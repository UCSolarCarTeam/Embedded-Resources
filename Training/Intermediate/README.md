# Solar Car Embedded Systems: Intermediate Training

Welcome! In this training you will learn how a microcontroller talks to the outside world: blinking an LED
(**GPIO**), reading a sensor (**I2C**), controlling a chip over **SPI**, and sending text to your computer
(**UART**). You will do it on the same kind of hardware we use on the car, using ST's **HAL** library.

---

## 1. Why STM32?

STM32 is a large family of microcontrollers from STMicroelectronics. We use them because:

- **Right peripherals for the car.** They have the hardware we need built in: GPIO, I2C, SPI, UART, ADCs,
  timers and CAN.
- **One family, many sizes.** From small low-power parts to fast ones, with the same tools and the same HAL.
  What you learn on one chip transfers to the others.
- **Free, official tools.** STM32CubeIDE (editor, compiler and debugger), STM32CubeMX (graphical pin and
  clock configuration, built into CubeIDE) and STM32CubeProgrammer.
- **Lots of documentation and community help.** Datasheets, reference manuals, example code, a wiki and a
  forum.
- **Arm Cortex-M core.** The same processor architecture used across the industry, so the skills carry over
  to other brands.

Our training board uses an **STM32H503CBT6** (STM32H5 family, Arm Cortex-M33).

---

## 2. Anatomy of an STM32 project

When you create a project in CubeIDE (or generate code from the `.ioc` file) you get something like this
(exact names vary a little with the CubeIDE version):

```
MyProject/
├── MyProject.ioc                 CubeMX configuration: pins, clocks, peripherals (the "source of truth")
├── Core/
│   ├── Inc/
│   │   ├── main.h                Pin name macros (e.g. Z_SPI_nCS_Pin) and includes
│   │   ├── stm32h5xx_hal_conf.h  Which HAL modules are enabled
│   │   └── stm32h5xx_it.h
│   └── Src/
│       ├── main.c                YOUR program starts here (main loop)
│       ├── stm32h5xx_it.c        Interrupt handlers
│       ├── stm32h5xx_hal_msp.c   Low-level setup of pins and clocks for each peripheral (generated)
│       └── system_stm32h5xx.c    Clock system startup
├── Drivers/
│   ├── CMSIS/                    Arm/ST core definitions (register names)
│   └── STM32H5xx_HAL_Driver/     The HAL library itself
├── Startup/                      Assembly that runs first after reset and then calls main()
├── STM32H503CBTX_FLASH.ld        Linker script: where code and data live in memory
└── Debug/                        Build output (the .elf you flash)
```

### What happens at power-up
1. The startup code runs and sets up memory.
2. `main()` calls `HAL_Init()`, `SystemClock_Config()` and the `MX_..._Init()` functions that CubeMX generated
   (GPIO, I2C, SPI, ...).
3. Your code runs, usually inside `while (1)`.

### The golden rule: USER CODE blocks
CubeMX regenerates `main.c` whenever you change the `.ioc`. Anything you write **outside** the markers is
**deleted**:

```c
/* USER CODE BEGIN 2 */
  // your code is safe here
/* USER CODE END 2 */
```

Always write inside a `USER CODE BEGIN ... / END ...` pair.

---

## 3. What is HAL, and why do we use it?

**HAL (Hardware Abstraction Layer)** is a set of libraries provided by STMicroelectronics to simplify the development process on STM32 microcontrollers. HAL provides a high-level interface for interacting with the MCU's peripherals like GPIO, SPI, UART, and more, allowing developers to write code that is more portable across different STM32 devices.

By using HAL, developers can avoid dealing directly with hardware registers, which speeds up development, improves readability, and reduces the complexity of peripheral configurations.

Without HAL, turning on a pin means finding the right register and bit in a 1000+ page reference manual:

```c
GPIOC->BSRR = (1U << 13);            // set PC13 (register level)
```

With HAL:

```c
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
```

**Why we use it**
- **Faster to learn and read.** Function names say what they do.
- **Portable.** The same calls work on other STM32 families.
- **CubeMX generates the setup code for you** using HAL.
- **Consistent.** Every peripheral follows the same patterns.

**Patterns you will see everywhere**

| Pattern | Meaning |
|---|---|
| `HAL_<PERIPHERAL>_<Action>()` | e.g. `HAL_I2C_Mem_Read`, `HAL_UART_Transmit`, `HAL_GPIO_TogglePin` |
| **Handles** (`hi2c1`, `hspi2`, `huart1`) | A struct holding a peripheral's configuration and state. You pass its address (`&hi2c1`) to every call |
| **Return status** `HAL_StatusTypeDef` | `HAL_OK`, `HAL_ERROR`, `HAL_BUSY`, `HAL_TIMEOUT`. **Always check it.** |
| **Timeouts** in milliseconds | Blocking calls give up after this long |
| **Blocking vs. `_IT` vs. `_DMA`** | Blocking waits until done. `_IT` (interrupt) and `_DMA` work in the background. This training only uses blocking calls |
| `HAL_Delay(ms)`, `HAL_GetTick()` | Wait, or read the milliseconds since boot |

**Trade-offs (be aware, not afraid).** HAL is a bit bigger and slower than writing registers by hand, and it
hides what the hardware does. That is why the lessons in this training also explain what happens on the
wires. ST also offers a thinner library called LL (Low Layer) if you ever need more control.

---

## 4. How to use this training

### What is in the folder

| File | Purpose |
|---|---|
| `peripheral_training.h` | **The selector.** Choose your training here with `ACTIVE_TRAINING`. Also shared names and settings |
| `peripheral_training.c` | The "test": calls your functions and stores results in `g_...` variables. **Do not edit** |
| `gpio_training.c` | GPIO lesson and your TODOs |
| `i2c_training.c` | I2C lesson, MC3479 accelerometer reference and your TODOs |
| `spi_training.c` | SPI lesson, MCP23S17 I/O expander and your TODOs |
| `uart_training.c` | UART lesson and your TODOs |

You only edit `gpio_training.c`, `i2c_training.c`, `spi_training.c` and `uart_training.c`.

### Step 1: Add the files to your project
Copy the `.c` files into `Core/Src` and `peripheral_training.h` into `Core/Inc`, then refresh the project
(F5) in CubeIDE.

### Step 2: Check the CubeMX settings
The training assumes these are already configured (open the `.ioc` and check):

| Peripheral | Setting |
|---|---|
| GPIO | PC13 = GPIO_Output (LED D1), PB8 = GPIO_Input (DIP switch BOOT1) |
| I2C | I2C1 enabled (handle `hi2c1`), standard 100 kHz or fast 400 kHz |
| SPI | SPI2 master, 8-bit, mode 0 (handle `hspi2`), baud prescaler **8 or higher**. `Z_SPI_nCS` and `Z_nRESET` as GPIO outputs with those user labels |
| UART | USART1 asynchronous, 115200 baud, 8 data bits, no parity, 1 stop bit (handle `huart1`) |

### Step 3: Hook it into `main.c`
Only two lines are needed. Remove any old exercise code from earlier trainings.

```c
/* USER CODE BEGIN Includes */
#include "peripheral_training.h"
/* USER CODE END Includes */
```

```c
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_SPI2_Init();
  /* ...the other MX_..._Init() calls CubeMX generated... */

  /* USER CODE BEGIN 2 */
  Peripheral_Training_Init();      // runs the IMU / expander setup if the chosen training needs it
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    Peripheral_Training_Run();     // runs the chosen training over and over
  }
  /* USER CODE END 3 */
```

### Step 4: Pick a training
In `peripheral_training.h`:

```c
#define ACTIVE_TRAINING   TRAINING_GPIO_LED
```

Change it, rebuild, flash. Nothing else in `main.c` changes.

| Training | You complete (file) | What success looks like |
|---|---|---|
| `TRAINING_GPIO_LED` | `SetLed`, `ToggleLed` (gpio) | The LED turns on, off, and toggles |
| `TRAINING_GPIO_SWITCH` | `ReadBoot1` (gpio) | The LED follows the DIP switch. `g_switch` changes |
| `TRAINING_I2C_PROBE` | All of Part 1 and `InitIMU` (i2c) | `g_status == HAL_OK`, `g_chip_id == 0xA4`, `g_wrong_addr != HAL_OK` |
| `TRAINING_I2C_ACCEL` | `ReadAcceleration`, `ReadAccelerationMg` (i2c) | `g_accel_raw` / `g_accel_mg` change when you tilt the board. Flat on a table, Z is about 1000 mg |
| `TRAINING_SPI_EXPANDER` | `WriteRegister`, `ReadRegister`, `InitExpander` (spi) | `g_init_status == HAL_OK`, `g_iodira == 0xF0`, `g_iodirb == 0xFF` |
| `TRAINING_SPI_LEDS` | `SetLeds` (spi) | The four expander LEDs count in binary |
| `TRAINING_SPI_PORTS` | `ReadPorts` (spi) | `g_ports` shows the pin levels (port A in the high byte) |
| `TRAINING_UART_PRINT` | `Print`, `TransmitBytes` (uart) | Text appears in your serial terminal |
| `TRAINING_UART_RECEIVE` | `ReceiveBytes` (uart) | Type 4 characters, they are echoed back |
| `TRAINING_UART_LED_TOGGLE` | `WaitForToggle` (uart) | Sending `LED_TOGGLE` + Enter toggles the LED |

Suggested order: GPIO, then I2C, then SPI, then UART.

### Step 5: Work through a file
1. **Read the lesson comment** at the top of the file.
2. Work through the functions top to bottom. Each has a skeleton: the HAL call is commented out with every
   parameter explained. Uncomment it and fill in the arguments.
3. Where you see `TODO`, write the code described. `Look at:` lines tell you which datasheet register to open.
4. Build, flash, and check the results (see below).
5. Try the `TASKS` list at the bottom of each file, and answer the questions in the comments.

### Checking your results
- **Debugger Live Expressions:** add the `g_...` variables from `peripheral_training.c`
  (for example `g_status`, `g_chip_id`, `g_accel_mg`). A value of `0` in a `HAL_StatusTypeDef` is `HAL_OK`.
- **Breakpoints:** the runners contain `__NOP();   /* breakpoint here */` lines. Put a breakpoint on them.
- **Serial terminal (UART):** use PuTTY, Tera Term or similar at **115200 8-N-1**.
  Wire it with a 3.3 V USB-serial adapter: board TX to adapter RX, board RX to adapter TX, and a common GND.
  For `LED_TOGGLE`, set the terminal to send **CR+LF** when you press Enter.

### If something does not work
- Check the **returned status** of every HAL call first.
- **I2C:** the HAL wants the 7-bit address **shifted left by 1** (`0x4C << 1`). Is the wiring and power OK?
- **SPI:** is chip select going **low** before and **high** after every transfer?
- **UART:** same baud rate on both sides? TX and RX crossed?
- **GPIO:** is the pin configured as output/input in CubeMX? Does a HIGH level turn the LED on or off?
  Check the schematic.
- Still stuck? Ask a lead before looking at the solutions.

---

## 5. Where to learn more

ST's wiki has step-by-step "Getting started" guides for each peripheral, with diagrams and example code:

**https://wiki.st.com/stm32mcu/wiki/Category:Getting_started_with_STM32_system_peripherals**

Pages most relevant to this training:
[GPIO](https://wiki.st.com/stm32mcu/wiki/Getting_started_with_GPIO),
[I2C](https://wiki.st.com/stm32mcu/wiki/Getting_started_with_I2C),
[SPI](https://wiki.st.com/stm32mcu/wiki/Getting_started_with_SPI),
[UART](https://wiki.st.com/stm32mcu/wiki/Getting_started_with_UART),
and for later: [EXTI (external interrupts)](https://wiki.st.com/stm32mcu/wiki/Getting_started_with_EXTI),
[DMA](https://wiki.st.com/stm32mcu/wiki/Getting_started_with_DMA),
[TIM (timers)](https://wiki.st.com/stm32mcu/wiki/Getting_started_with_TIM),
[ADC](https://wiki.st.com/stm32mcu/wiki/Getting_started_with_ADC).

Also keep these open while you work: the [MC3479 datasheet](https://www.memsic.com/Public/Uploads/uploadfile/files/20220522/MC3479Datasheet(APS-048-0072v1.2).pdf), the [MCP23S17 datasheet](https://ww1.microchip.com/downloads/aemDocuments/documents/APID/ProductDocuments/DataSheets/MCP23017-MCP23S17-16-Bit-IO-Expander-with-Serial-Interface-DS20001952.pdf), and the **board schematic**.
