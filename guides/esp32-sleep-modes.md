# ESP32 Sleep modes

ESP32 contains the following power saving modes: Light-sleep, and Deep-sleep.

In Light-sleep mode, the digital peripherals, most of the RAM, and CPUs are clock-gated and their supply voltage is reduced. Upon exit from Light-sleep, the digital peripherals, RAM, and CPUs resume operation and their internal states are preserved.

In Deep-sleep mode, the CPUs, most of the RAM, and all digital peripherals that are clocked from APB_CLK (Advanced Peripheral Bus Clock) are powered off. The only parts of the chip that remain powered on are:
- [RTC controller](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/system_time.html)
- [ULP coprocessor](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/ulp.html)
- [RTC fast memory](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/memory-types.html#rtc-fast-memory)
- [RTC slow memory](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/memory-types.html#rtc-slow-memory)

The simplest way to use sleep modes is simply by specifying the time the board should go to sleep, as described in the code example below. However, there are several other possible wakeup sources in Deep-sleep and Light-sleep modes. These sources can also be combined so that the chip will wake up when any of the sources are triggered. Wakeup sources can be enabled using `esp_sleep_enable_X_wakeup` APIs and can be disabled using `esp_sleep_disable_wakeup_source()` API.

A list of the wakeup sources can be found here:<br>
https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/sleep_modes.html#wakeup-sources

Once wakeup sources are configured, the application can enter sleep mode using `esp_light_sleep_start()` or `esp_deep_sleep_start()` APIs. At this point, the hardware will be configured according to the requested wakeup sources, and the RTC controller will either power down or power off the CPUs and digital peripherals.

You can find a full overview of the sleep modes APIs and wakeup sources here:<br>
https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/sleep_modes.html

## Code examples
The following code presents a simple use of the function `esp_deep_sleep()` from the `esp_sleep.h` library. It puts the ESP32 in deep sleep five times for ten seconds, printing to the serial output when it does so.
```C
#include "esp_sleep.h"

#define DEEP_SLEEP_SECONDS 10 // Time that will be slept defined as a precompiler constant, in seconds

void sleep_for_sec(int time_in_sec){
    Serial.print("Entering deep sleep for ");
    Serial.print(time_in_sec);
    Serial.println(" seconds.");

		// The value is multiplied by 1 000 000 to obtain seconds, as the function uses microseconds.
		// The "LL" at the end of the number specifies it is a Long Long integer for additional precision
		// This prevents rounding errors, especially when dealing with shorter times
    esp_deep_sleep(1000000LL * time_in_sec);
    Serial.println("Waking up!");
		return;
}

void main(){

		for(int i =0; i<5; i++){
			Serial.println("Doing stuff in between sleep times !");
			sleep_for_sec(DEEP_SLEEP_SECONDS);
		}
	return;
}
```
A more complex example using a servers to synchronize internal and real-world time is available here:<br>
https://github.com/espressif/esp-idf/tree/49551cc48cb3cdd5563059028749616de313f0ec/examples/protocols/sntp
## References
The complete documentation on ESP-IDF and RTOS features is available here :<br>
https://docs.espressif.com/projects/esp-idf/en/latest/esp32/index.html

The part that pertains to sleep mode is available here :<br>
https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/sleep_modes.html