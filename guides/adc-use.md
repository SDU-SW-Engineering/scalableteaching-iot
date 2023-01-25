
# ESP32 ADC setup and use

## Library
The following guide uses definitions found in `adc.h` for the driver, and `esp_adc_cal.h` for the adc calibration. If the linter can't find the libraries, add the following line to the C/C++ include path in Vscode parameters to recursively search them:
```
<ESP install folder>/esp-idf/components/driver/**
```
> **Note**: this library is deprecated in favor of ADC oneshot and continuous mode libraries, that allow for greater possibilities, but more complex to use. The links for the related references are available in the *Reference* section of this guide.

## ADC Pins
The following table describes the IO pins that are associated with ADC1 and ADC2 modules. As can be seen from the table, there are 8 ADC1 channels, numbered from 0 to 7 and 10 ADC2 channels, numbered from 0 to 9. If you are measuring analog signal from pin GPIO34, for example, you will refer to it as ADC1_CHANNEL_6 in your code.<br>
> **Note**: Be mindful that ADC2 is used by the Wi-Fi driver, therefore the application can only use ADC2 when the Wi-Fi driver has not started.

|  ADC1 channel  | GPIO pin |
|:--------------:|:--------:|
| ADC1_CHANNEL_0 | GPIO36   |
| ADC1_CHANNEL_1 | GPIO37   |
| ADC1_CHANNEL_2 | GPIO38   |
| ADC1_CHANNEL_3 | GPIO39   |
| ADC1_CHANNEL_4 | GPIO32   |
| ADC1_CHANNEL_5 | GPIO33   |
| ADC1_CHANNEL_6 | GPIO34   |
| ADC1_CHANNEL_7 | GPIO35   |

|  ADC2 channel  | GPIO pin |
|:--------------:|:--------:|
| ADC2_CHANNEL_0 | GPIO4    |
| ADC2_CHANNEL_1 | GPIO0    |
| ADC2_CHANNEL_2 | GPIO2    |
| ADC2_CHANNEL_3 | GPIO15   |
| ADC2_CHANNEL_4 | GPIO13   |
| ADC2_CHANNEL_5 | GPIO12   |
| ADC2_CHANNEL_6 | GPIO14   |
| ADC2_CHANNEL_7 | GPIO27   |
| ADC2_CHANNEL_8 | GPIO25   |
| ADC2_CHANNEL_9 | GPIO26   |

> **Note**: some ESP32 model-specific restriction apply :
> - On ESP32 DevKitC: GPIO 0 cannot be used due to external auto program circuits.
> - on ESP-WROVER-KIT: GPIO 0, 2, 4 and 15 cannot be used due to external connections for different purposes.

## ADC Input Voltage range
Before feeding into the ADC modules, the analog signal is attenuated. Depending on the attenuation parameter, the range of ADC is different. The table below listed the attenuation parameters and their respective input ranges. The table shows that the ESP32 ADC only works reliably in certain range. This is a limitation of the ESP32 ADC.

| Attenuation parameter | Input range (mV) |         Note         |
|:---------------------:|:----------------:|:--------------------:|
| ADC_ATTEN_DB_0        | 100 ~ 950        | No attenuation (0dB) |
| ADC_ATTEN_DB_2_5      | 100 ~ 1250       | 2.5 dB attenuation   |
| ADC_ATTEN_DB_6        | 150 ~ 1750       | 6 dB attenuation     |
| ADC_ATTEN_DB_11       | 150 ~ 2450       | 11 dB attenuation    |

To setup attenuation parameter for a channel of ADC1, you use the API `adc1_config_channel_atten()`. For example, to set 11 dB attenuation for ADC1 channel 6, you have to use the following:
```C
adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_11);
```
Similarly, to configure attenuation for a ADC2 channel, you use `adc2_config_channel_atten()` function in the adc driver.

## ADC bit width configuration
By default, the ADC uses 12-bits wide values. Use the following:
```C
adc1_config_width(ADC_WIDTH_BIT_DEFAULT);
// or if you are using ADC2 :
adc2_config_width(ADC_WIDTH_BIT_DEFAULT);
```
Other possible values are `ADC_WIDTH_BIT_9`, `ADC_WIDTH_BIT_10`, `ADC_WIDTH_BIT_11`, `ADC_WIDTH_BIT_12`.
> **Note**: you have to call the configuration function before the first time you read input from an ADC channel, even if you are using the default bit width.

## Read ADC raw values
To read the raw value from an ADC channel, use the following:
```C
int raw_value = adc1_get_raw(ADC1_CHANNEL_6); // Reads on ADC1 channel 6
```

## Read ADC converted voltage values
It is also possible to use the calibration to read raw values converted to milivolt values. To do so, you first need to characterize the ADC with the calibration:
```C
esp_adc_cal_characteristics_t adc1_chars; // Stores the ADC characteristics

// First value is the ADC to characterize, second is attenation parameter as seen previously
esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_DEFAULT, 0, &adc1_chars);
```
Then you can use the `esp_adc_cal_raw_to_voltage()` function to convert the raw input to voltage values, using the characterization that we made and the raw reading:
```C
uint32_t reading = adc1_get_raw(ADC1_CHANNEL_6);
uint32_t voltage = esp_adc_cal_raw_to_voltage(reading, adc1_chars);
```

## Complete example
```C
#include "adc.h"
#include "esp_adc_cal.h"
#include "esp_log.h"
#include "esp_sleep.h"

#define TAG "ADC EXAMPLE" // For logging purposes
#define SAMPLE_INTERVAL 3 // Sample interval, in seconds

void init_adc1(adc1_channel_t channel, esp_adc_cal_characteristics_t *adc_chars, adc_atten_t attenuation){
	adc1_config_channel_atten(channel, attenuation);
	adc1_config_width(ADC_WIDTH_BIT_DEFAULT);
	esp_adc_cal_characterize(ADC_UNIT_1, attenuation, ADC_WIDTH_BIT_DEFAULT, 0, adc_chars);
	return;
}

void main(){
	esp_adc_cal_characteristics_t adc1_chars;

	init_adc1(ADC1_CHANNEL_6, &adc1_chars, ADC_ATTEN_DB_11);

	while(1){ // Continuously reads the voltage on GPIO34
		uint32_t voltage = esp_adc_cal_raw_to_voltage(adc1_get_raw(ADC1_CHANNEL_6), adc1_chars);
		ESP_LOGI(TAG, "ADC1_CHANNEL_6: %d mV", voltage); // Logs the voltage value
		esp_sleep_enable_timer_wakeup(1000000LL * SAMPLE_INTERVAL)
		esp_light_sleep_start(); // Sleeps for the specified interval
	}
}
```

## References
The complete API and macro references are available here: <br>
- [ADC Reference](https://docs.espressif.com/projects/esp-idf/en/release-v3.3/api-reference/peripherals/adc.html)
- [Reference for Oneshot mode](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/adc_oneshot.html)
- [Reference for Continuous mode](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/adc_continuous.html)
- [Reference for ADC calibration](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/adc_calibration.html)