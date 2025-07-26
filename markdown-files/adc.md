<link rel="stylesheet" href="../styles.css">

# Analog-to-Digital Converter (ADC)
----
## Signals
A **signal** is a detectable physical quantity (e.g. voltage, current, etc.) by which information can be transmitted. Typically, microcontrollers detect signals as voltages.

There are two standard frameworks used to view and analyze signals: 

- **continuous-time**:  time variations are considered on an infinitesimal scale
- **discrete-time**: time variations are considered in discrete steps

<img src="../images/cont-time.png" alt="Cont vs Disc" width=70%>

Examples of continuous variables: temperature, distance, etc.

Examples of discrete variables: ice cream flavours, number of people, etc.


The real world is analog, but our microcontroller is digital!

<div style="background-color: #f0f8ff; border-left: 4px solid #2196F3; padding: 1em; margin: 1em 0; border-radius: 6px; font-family: inherit; color: #4f4f4f;">

**Extra**

Typically, discrete values cannot be broken down more!!

</div>

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

We can convert the analog to a digital representation by using sampling.

Sampling is measuring the signal at a periodic rate.

<img src="../images/adc.png" alt="Cont vs Disc" width=70%>

- talk abt resolution i guess lol