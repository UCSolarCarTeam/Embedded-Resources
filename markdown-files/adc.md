<link rel="stylesheet" href="../styles.css">

# Analog-to-Digital Converter (ADC)
----
## Signals
A **signal** is a detectable physical quantity (e.g. voltage, current, etc.) by which information can be transmitted. Typically, microcontrollers detect signals as voltages.

There are two standard frameworks used to view and analyze signals: 

- **continuous-time**:  time variations are considered on an infinitesimal scale
- **discrete-time**: time variations are considered in discrete steps

<img src="../images/cont-time.png" alt="Cont vs Disc" width=70%>

<div style="background-color: #fff9db; border-left: 4px solid #fbc02d; padding: 1em; margin: 1em 0; border-radius: 6px; font-family: inherit; color: #4f4f4f;">

**Example**

Examples of continuous variables: temperature, distance, etc.
Examples of discrete variables: ice cream flavours, number of people, etc.

 </div>

<div style="background-color: #f0f8ff; border-left: 4px solid #2196F3; padding: 1em; margin: 1em 0; border-radius: 6px; font-family: inherit; color: #4f4f4f;">

**Extra**

Typically, discrete values cannot be broken down more!!

</div>

The real world is analog, but our microcontroller is digital!


## Digital vs Analog

An **analog** signal refers to a continuously-valued signal, meanwhile…

A **digital** signal refers to a discretely-valued signal, where its magnitude is determined by quantization of each discrete point in time

- **quantization** assigns a single number to represent a range of magnitudes of a continuous signal


The world is often analog, but our microcontrollers can only operate with discrete values…

So how do we resolve this?

<div style="background-color: #f0f8ff; border-left: 4px solid #2196F3; padding: 1em; margin: 1em 0; border-radius: 6px; font-family: inherit; color: #4f4f4f;">

**Extra**

Ok so whats the difference between analog, digital, continuous, and discrete?

- In my mind, I think of it as how discrete-time and continuous-time describe the x-axis (time), where continuous means we know the y-axis value at every single point in time, and discrete meaning we only know the y-axis value at specific points in time. Analog and digital can be thought of as describing the y-axis (or the magnitude), where analog means the y-axis value can be any value, but a digital signal is one that samples a signal and performs quantization, resulting in a y-axis value that is discrete! ADC is necessary because digitally, we cannot represent something continuous (because everything needs some sort of bit representation), and so we quantize the values using a certain resolution. A higher bit resolution means that the y-axis value can be more specific/similar to its true real world value.

</div>

## Analog-to-Digital Converter (ADC)

Physical quantities are captured by some sort of sensor, and are usually reflected as something such as a voltage (usually with infinite values in between due to being continuous). 

We can convert the analog signal to a digital representation by using sampling, and quantization.

- **Sampling** is measuring the signal at a periodic rate

<img src="../images/adc.png" alt="ADC" width=70%>

**Resolution** is defined as: *resolution* = Vref/(2^n)
- It is the number of volts between successive digital encodings
- n = number of biys for each sample
- This equation assumes a minimum voltage of 0V

<div style="background-color: #fff9db; border-left: 4px solid #fbc02d; padding: 1em; margin: 1em 0; border-radius: 6px; font-family: inherit; color: #4f4f4f;">

**Example**

For example, this is how 10-bit resolution would work:

<img src="../images/resolution.png" alt="Resolution" width=70%>

Since there are 10 bits, 2^10 is 1024. This means there are 1024 discrete values we can use (0-1023). If we had a sensor to detect a voltage ranging from 0-3V, receiving the ADC value of 1002 would mean that it is currently sensing a voltage of (1002/1024) * 3V = 2.94V.

</div>

Great! Now how do we use ADC in the context of our system???

## Using ADC with an STM32

<div style="background-color: #f0f8ff; border-left: 4px solid #2196F3; padding: 1em; margin: 1em 0; border-radius: 6px; font-family: inherit; color: #4f4f4f;">

**Extra**

STM32Cube includes:

• STM32CubeMX, a graphical software configuration tool that allows the generation of C initialization code using graphical wizards.
• A comprehensive embedded software platform, delivered per Series (such as STM32CubeF4 for STM32F4 Series)
- The STM32Cube HAL, STM32 abstraction layer embedded software ensuring maximized portability across the STM32 portfolio. HAL APIs are available for all peripherals.
- Low-layer APIs (LL) offering a fast light-weight expert-oriented layer which is closer to the hardware than the HAL. LL APIs are available only for a set of peripherals.
- A consistent set of middleware components such as RTOS, USB, TCP/IP and Graphics. 
- All embedded software utilities, delivered with a full set of examples.

</div>

**Step 1**
Go to the .ioc file. It will look similar to this:

INSERT IMAGE

Click on "Analog". Here you can select an ADC to use! (for example select ADC1)



**Step 2**

--- 

## Useful Things!

<a href="https://www.disca.upv.es/aperles/arm_cortex_m3/llibre/st/STM32F439xx_User_Manual/group__adc__exported__functions.html" style = "color: #f0f8ff" >STM32F439xx HAL User Manual (ADC)
</a>

<a href="https://deepbluembedded.com/stm32-adc-tutorial-complete-guide-with-examples/#:~:text=ADC%20Example%20Applications-,Introducing%20STM32%20ADC,trigger%20it%20to%20start%20conversion" >STM32F439xx HAL User Manual (ADC)
</a>

---
Author: Millaine Li
Last Updated: July 26, 2025
Note: Took a lot of things from my lectures lol 

