# ESP32 GPIO use

## Library
In order to use the functions presented in this guide it is necessary to include `gpio.h` in your code. If the linter can't find the libraries, add the library folders to the C/C++ include path in Vscode parameters. It should be located here :
```
<ESP install folder>/esp-idf/components/driver/include/driver
```

## GPIO output
To set the direction of a GPIO pin as output, use the `gpio_set_direction()` function and library-defined macros as following:
```C
gpio_set_direction(GPIO_NUM_0, GPIO_MODE_OUTPUT) // Sets the GPIO pin 0 as output mode
```
It is first needed to set the pin as output mode in order to output to it. To set the output as high or low on a pin, use the `gpio_set_level()` function and library-defined macros as following:
```C
gpio_set_level(GPIO_NUM_0, 1) // Sets the GPIO pin 0 output as high
```
## GPIO input
To set the direction of a GPIO pin as input, use the `gpio_set_direction()` function and library-defined macros as following:
```C
gpio_set_direction(GPIO_NUM_0, GPIO_MODE_INPUT) // Sets the GPIO pin 0 as input mode
```
It is first needed to set the pin as input mode in order to read from it. To read the input, use the `gpio_get_level()` function and library-defined macros as following:
```C
gpio_get_level(GPIO_NUM_0) // Reads the GPIO pin 0 input, which will be either 1 or 0 (high or low)
```

## References
The complete API and macro reference is available here: <br>
https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/gpio.html