
# ESP32 ADC setup and use

## Library
The following guide uses definitions found in `adc.h` for the driver, and `esp_adc_cal.h` for the adc calibration.

## ADC Pins
The following table describes the IO pins that are associated with ADC1 and ADC2 modules. As can be seen from the table, there are 8 ADC1 channels, numbered from 0 to 7 and 10 ADC2 channels, numbered from 0 to 9. If you are measuring analog signal from pin GPIO34, for example, you will refer to it as ADC1_CHANNEL_6 in your code.<br>
**Be mindful that ADC2 is used by the Wi-Fi driver, therefore the application can only use ADC2 when the Wi-Fi driver has not started.**

|  ADC1 channel  | GPIO pin |  ADC2 channel  | GPIO pin |
|:--------------:|:--------:|:--------------:|:--------:|
| ADC1_CHANNEL_0 | GPIO36   | ADC2_CHANNEL_0 | GPIO4    |
| ADC1_CHANNEL_1 | GPIO37   | ADC2_CHANNEL_1 | GPIO0    |
| ADC1_CHANNEL_2 | GPIO38   | ADC2_CHANNEL_2 | GPIO2    |
| ADC1_CHANNEL_3 | GPIO39   | ADC2_CHANNEL_3 | GPIO15   |
| ADC1_CHANNEL_4 | GPIO32   | ADC2_CHANNEL_4 | GPIO13   |
| ADC1_CHANNEL_5 | GPIO33   | ADC2_CHANNEL_5 | GPIO12   |
| ADC1_CHANNEL_6 | GPIO34   | ADC2_CHANNEL_6 | GPIO14   |
| ADC1_CHANNEL_7 | GPIO35   | ADC2_CHANNEL_7 | GPIO27   |
|                |          | ADC2_CHANNEL_8 | GPIO25   |
|                |          | ADC2_CHANNEL_9 | GPIO26   |

Additionally, some ESP32 model-specific restriction apply :
- On ESP32 DevKitC: GPIO 0 cannot be used due to external auto program circuits.
- on ESP-WROVER-KIT: GPIO 0, 2, 4 and 15 cannot be used due to external connections for different purposes.

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
By default, the ADC uses 12-bits wide values.<br>**However, you need to call the configuration function before the first time you read input from an ADC channel.** <br>Use the following:
```C
adc1_config_width(ADC_WIDTH_BIT_DEFAULT);
// or if you are using ADC2 :
adc2_config_width(ADC_WIDTH_BIT_DEFAULT);
```
Other possible values are `ADC_WIDTH_BIT_9`, `ADC_WIDTH_BIT_10`, `ADC_WIDTH_BIT_11`, `ADC_WIDTH_BIT_12`.

## Read ADC raw values
To read the raw value from an ADC channel, use the following:
```C
int raw_value = adc1_get_raw(ADC1_CHANNEL_6); // Reads on ADC1 channel 6
```

## References
The complete API and macro references are available here: <br>
- [ADC Reference](https://docs.espressif.com/projects/esp-idf/en/release-v3.3/api-reference/peripherals/adc.html)
- [Reference for Oneshot mode](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/adc_oneshot.html)
- [Reference for Continuous mode](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/adc_continuous.html)
- [Reference for ADC calibration](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/adc_calibration.html)