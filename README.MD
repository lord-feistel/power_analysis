
# Power analysis attack over RSA


## Index
## Index

- [Introduction](#introduction)
- [Power Analysis Attacks](#power-analysis-attacks)
- [RSA: A Short Introduction](#rsa-a-short-introduction)
- [RSA Example](#rsa-example)
- [Equipment](#equipment)
- [Measuring Power: A Short Introduction](#measuring-power-a-short-introduction)
  - [Ohm's Law](#ohms-law)
  - [Kirchhoff's Voltage Law (KVL)](#kirchhoffs-voltage-law-kvl)
  - [Voltage Divider](#voltage-divider)
  - [Shunt Resistor](#shunt-resistor)
- [Example Power Measurement](#example-power-measurement)
- [Fast Exponentiation](#fast-exponentiation)
- [Fast Exponentiation in Arduino (Atmega328P)](#fast-exponentiation-in-arduino-atmega328p)
- [Results](#results)
- [Conclusion](#conclusion)
- [References](#references)



### Introduction

Recently,  I observed people implementing cryptography for Arduino by themselves like state in this topic in stackoverflow:

https://stackoverflow.com/questions/39189065/rsa-encryption-decryption-functions-for-arduino

Several of them can be found over the internet, some by the way are in well-knowm libraries.

I decide to do this small PoC ( Proof of concept )to show why is important not invented your own cryptography algorithm, but also use a robust implementation of such a algorithms.

This PoC  performs an side channel attack ( power analysis attack ) against a bad implementation of an auxiliary routine used in the RSA implementation ( fast exponentiation).

A side-channel attack is a method of compromising a cryptographic system by exploiting indirect information leakage rather than directly attacking the cryptographic algorithm or protocol itself.

This type of leakage can originate from various sources such as timing information, power consumption, electromagnetic emissions, or even sound.

Such attacks can be highly effective in compromising cryptographic systems like RSA without requiring the attacker to solve the underlying mathematical problems that ensure the security of the cryptographic scheme (Kocher, Jaffe, & Jun, 1999).

This paper will perform a power analysis attack on a well-known vulnerability in an implementation of the RSA algorithm in a firmware for  Arduino ( Atmega328P).

> Note I did it on the rush, please forgive me for the spells / grammar errors that eventually you will find.

### Power Analysis Attacks

Power analysis attacks involve measuring the power consumption of a device during cryptographic operations. 

Differential Power Analysis (DPA) involves statistical analysis of power consumption patterns across multiple cryptographic operations to extract secrets, making it more sophisticated than Simple Power Analysis (SPA), which directly correlates power fluctuations with specific cryptographic operations to deduce secrets.

Differential Power Analysis (DPA) and Simple Power Analysis (SPA) can be used to extract private keys by analyzing patterns in power consumption during RSA computations. 

These attacks can reveal the private key by identifying distinct power usage patterns associated with different key bits (Kocher, Jaffe, & Jun, 1999).

### RSA: A Short Introduction

RSA (Rivest-Shamir-Adleman) is a widely used public-key encryption algorithm named after its inventors: Ron Rivest, Adi Shamir, and Leonard Adleman, who introduced it in 1977 (Paar & Pelzl, 2010). 

It remains one of the most secure methods for transmitting data securely over the internet.

One of the foundations of RSA's security lies in the difficulty of factoring large composite numbers into their prime factors (Menezes, van Oorschot, & Vanstone, 1996). 

This problem, known as the factoring problem, involves finding the prime numbers that multiply together to form a given large number. 

RSA encryption relies on the assumption that this factoring problem is computationally difficult enough to make it impractical to break the encryption by factoring the modulus into its prime factors (Menezes, van Oorschot, & Vanstone, 1996).


### RSA Example

The **Figure 1** illustrates the RSA encryption and decryption process using a simple example. 

![RSA Example](https://github.com/lord-feistel/power_analysis/blob/main/images/rsa_example.jpg)


**Figure 1** - RSA example. 

Please note that in this case, `3` and `33` are public. The number `7` in the example is the private key.

The **Phi (N)** function, Euler's totient function, computes all coprime numbers in the interval from `1` to `33`. 

The value `33` is obtained from the multiplication of `P` and `Q`; in this case, `11` multiplied by `3`.

The result of the Phi function is obtained by multiplying `(P - 1)` by `(Q - 1)`; in this case, `10` multiplied by `2`.

The operation `e<sup>-1</sup> mod 20` denotes the modular inverse operation (Menezes, van Oorschot, & Vanstone, 1996).

> **Note:** If you wish to delve deeper into RSA, which is not necessary to understand this paper. 
> There is a quick introduction to these basic number theory operations within this repository the file **number_theory.md**. 
> The explanation can enhance your understanding of RSA operations.


### Equipament

The experiment used an osciloscope DS1102 (presented in the **Figure 2**) manufactured by Rigol.

The osciloscope's manual can be found in the references (RIGOL Technologies, Inc., 2017).

A generic power supply was used either ( presented in **Figure 3**).

![osciloscope](https://github.com/lord-feistel/power_analysis/blob/main/images/osciloscope.jpg)

**Figure 2** - Oscilloscope used in the experiment.  


![power_supply](https://github.com/lord-feistel/power_analysis/blob/main/images/power_supply.jpg)


**Figure 3** - Power supply used in the experiment.  


### Meansuring power a short introduction

### Ohm Law

Ohm's Law is a fundamental principle in the field of electrical engineering and physics. 

It states that the current flowing through a conductor between two points is directly proportional to the voltage across the two points and inversely proportional to the resistance between them (Boylestad, 2015). 

The **Figure 4** shows an circuit and the  Ohm's law. 

![ohm_law](https://github.com/lord-feistel/power_analysis/blob/main/images/ohm_law.jpg)


**Figure 4** - Ohm law illustration.  

The Ohm law implies that if you increase the voltage across a conductor, the current will also increase, provided the resistance remains constant(Johnson & Hilburn, 2013). **Figure 5** present an example of Ohm's law application which the goal is to find the current in the circuit.


![ohm_example](https://github.com/lord-feistel/power_analysis/blob/main/images/ohm_example.jpg)


**Figure 5** - Ohm law example.


### Kirchoff law and

Kirchhoff's Voltage Law (KVL) is a fundamental principle in electrical engineering and physics (Boylestad, 2015). 

It states that the sum of all electrical potential differences (voltages) around any closed network or loop is zero (Boylestad, 2015).

The **Figure 6** ilustrates the Kirchhoff's voltage law.

![kirchoff_lay](https://github.com/lord-feistel/power_analysis/blob/main/images/kirchoff_law.jpg)

**Figure 6** - Kirchhoff law illustration.  

There is an  example of the  Kirchhoff's law's application in the **Figure 7**  in order to find the current over the
resistors `R1` and `R2`.

![kirchoff_example](https://github.com/lord-feistel/power_analysis/blob/main/images/kirchoff_example.jpg)

**Figure 7** - Kirchhoff law example. 

### Voltage divider

The voltage divider is a consequence of Kirchhoff's Voltage Law (KVL) and states a way to calculates the **Vout** that is the voltage between
the resistor `R1`and `R2`. 

The formula of the voltage divider  is presented in the **Figure 8**. 

An example of voltage divider application is presented in the **Figure 9**.

![voltage_divisor](https://github.com/lord-feistel/power_analysis/blob/main/images/voltage_divisor.jpg) 

**Figure 8** - Voltage divider illustration.

![voltage_divisor_example](https://github.com/lord-feistel/power_analysis/blob/main/images/voltage_divisor_example.jpg)

**Figure 9** - Voltage divider example. 

### Shunt Resistor

A shunt resistor is a low-value resistor placed in series with the circuit's power supply to measure the current flowing through the circuit.

Using a Shunt to meansure current is one of the techniques utlized in modern multimeters. (Boylestad, 2015).

Measuring the voltage drop across the shunt resistor and knowing its resistance gives enough information to  calculate the current using Ohm's Law.

To measure the current consumption of an Arduino device it is need to place a shunt resistor in series with the VCC ( positive ).

The way it wil be connected is presented in the  **Figure 10**. 

> **Note 1:** Please note that in the PoC,  instead use the arduino Uno board the target ( microcontroller atmega328p) is transfered to a separated breadboard as presented in the **Figure 11**. It allows to easier manipulate the pinout of the microcontroller not requiring soldering.

> **Note 2:** If you don't know how to do that, my previous article showing how glitching works teaches how to do that and can be found at 
> https://github.com/lord-feistel/hardware_hacking_lab) 

![voltage_divisor_arduino](https://github.com/lord-feistel/power_analysis/blob/main/images/voltage_divisor_arduino.jpg) 

**Figure 10** - Shunt with Arduino. 


![arduino_shunt](https://github.com/lord-feistel/power_analysis/blob/main/images/grapping_shunt.jpg)


**Figure 11** - Circuit of the shunt in the breadboard.  


### Example of power measurement 

To demonstrate the measurement of current consumption using a shunt resistor , a LED (Sedra & Smith, 2014) will be connected to the microcontroller's GPIO (**Figure12**) and the osciloscope will be used to observe how it affects the power consumption over the shunt resistor in the situations where the LED is on or off. 

> Observe to extract the Key or observing the charger effect over the power consumption is not needed to use the Ohms law to obtain the current, only the voltage drop is already enough (Johnson & Hilburn, 2013).

![power_consumption_led](https://github.com/lord-feistel/power_analysis/blob/main/images/complete_setup.jpg)

**Figure 12** - Power measurement.  


To better observe it, please check the  **Video 1** which shows how the voltage drop when led is on.

[![Video 1: Power consumption](https://github.com/lord-feistel/power_analysis/blob/main/images/leb_tumb.jpg)](https://youtube.com/shorts/cYBIXpIfJK8)

**Video 1** - Voltage drop because led consumption.

The following code was utilized to blink the led. It also can be found in this repository.

```C
const int PIN_CHARGE = 9 ;
void setup() {
  pinMode(PIN_CHARGE, OUTPUT);

}

void loop() {
  digitalWrite(PIN_CHARGE, HIGH); 
  delay(10);                      
  digitalWrite(PIN_CHARGE, LOW);   
  delay(10);    

}

```

It is important to state that this voltage drop also occurs when an complex calculation happens (Kocher, Jaffe, & Jun, 1999). 

The following code causes the Voltage drop presented in the **Figure 13**



```C
void setup() {

}

void loop() {
 
    volatile unsigned long i = 0;
    i = ((i + 1) * (i - 1) + (i * i) - (i / 2) * (i % 3) + (i * i * i * i)) * ((i + 2) * (i - 2) + (i * i) - (i / 3) * (i % 5) + (i * i * i * i));
    delayMicroseconds(100);

}

```

If the voltage drop reflects of calculation, thus it can be used to determine the data which is being processed.

![heavy_calculus](https://github.com/lord-feistel/power_analysis/blob/main/images/heavy_calculus.jpg)


**Figure 13** - Power consumption in the heavy calculation.  


## Fast exponentiation

The conventional way to perform the power operation is multipling the base `n` times.

Suppose 2<sup>3</sup> will result in ```2*2*2``` since `2`is the base and `3`is n. 

It works very good, but not efficiently enough to makes RSA feasible. 

In order to achieve such a immplementation it is used the **fast exponentiation** algorithm. 

Fast exponentiation, also known as exponentiation by squaring, is an efficient method for raising a number to a power. 

Following the pseudo-code for the fast exponentiation can be found.


```C

function fast_exponentiation(a, b):
    result = 1
    base = a
    exponent = b

    while exponent > 0:
        if (exponent % 2 == 1):   // If exponent is odd
            result = result * base
        base = base * base       // Square the base
        exponent = exponent // 2  // Divide exponent by 2

    return result

```

.


The steps of the fast exponentiationof 2<sup>4</sup> can be found in the  **Table 1** 


| Iteration | Base value   | Exponent in Binary         | Operation |     Result                |
|-----------|--------------|----------------------------|-----------|---------------------------|
| Initial   | 2            | 100                        | Start     | 1                         |
| 1         | 4            | 010                        | Square    | 1                         |
| 2         | 16           | 001                        | Square    | 1                         |
| 3         | 256          | 000                        | Multiply  | 16                        |
| Final     | -            | -                          | End       | 16                        |

**Table 1** - Iterations of fast exponentiation of  2<sup>4</sup>.

Following the process is explained : 

```
- **Initialization:**  
  Start with base = 2 ,  exponent = 4  ( binary 100) , result = 1.

- **Iteration 1:**  exponent = 4  (binary 100, even)  
  Square base  to get  4 .  
  result remains  1.

- **Iteration 2:**  exponent = 2 (binary 010, even)  
  Square  base  to get  16 .  
  result remains 1.

- **Iteration 3:**  exponent = 1  (binary: 001, odd)  
  Multiply result by a = 16  to get 16.  
  result becomes 16.

- **Final:**  n = 0  (binary: 000)  
  The loop ends with result = 16.
```

Note that for smaller numbers nothing change or it will get worser, however for big numbers it obtains a significant achievement in the efficiency.

It reduces the number of multiplicative operations compared to the naive approach, which is particularly useful for large exponents. 

**Table 2** shows a comparsion of the iterations for such a number using the naive exponentiation and the fast exponentiation. 

Fast exponentiation is critical in RSA for both encryption and decryption processes, as these processes involve raising large numbers to large powers modulo some other large number (Paar & Pelzl, 2010).

As presented in the `RSA example` section the key is the exponent and usualy it will be a very large number.



| Exponent (b) | Binary (b) | Conventional Exponentiation Operations | Fast Exponentiation Operations |
|--------------|------------|----------------------------------------|--------------------------------|
| 1            | 1          | 1                                      | 1                              |
| 2            | 10         | 1                                      | 1                              |
| 4            | 100        | 3                                      | 2                              |
| 8            | 1000       | 7                                      | 3                              |
| 16           | 10000      | 15                                     | 4                              |
| 32           | 100000     | 31                                     | 5                              |
| 64           | 1000000    | 63                                     | 6                              |
| 128          | 10000000   | 127                                    | 7                              |
| 256          | 100000000  | 255                                    | 8                              |
| 512          | 1000000000 | 511                                    | 9                              |
| 1024         | 10000000000| 1023                                   | 10                             |

**Table 2** - Comparsion of effiency between conventional exponentiation and fast exponentiation.

### Fast exponentiation in Arduino (Atmega328P)

An fast exponentiation was implemented in the arduino and uploaded in the atmega328p. As it is a PoC we implemented it in the easiest way to be visualized. 

For instance, usually it is utilized shift operation over an integer variable, but we implemented the exponent as an array to be better understood.

Note the exponent representing the key is the array ``` {0, 1, 0, 1, 0, 1, 0, 1} ``` which will create a pattern in the meansure acquired by the osciloscope as a proof of that it works.

```C

#include <Arduino.h>

volatile long long dumb_vulnerableExponentiation(volatile long long base, 
              const volatile int* exponentArray, volatile int arrayLength, volatile long long modulo) {
    volatile long long result = 1;
    base %= modulo;

    for (volatile int i = 0; i < arrayLength; ++i) {
        result = (result * result) % modulo;
        if (exponentArray[i] == 1) {
            result = (result * base) % modulo;
        }
    }

    return result;
}

void setup() {
}

void loop() {
    volatile long long base = 3;
    volatile long long modulo = 1000000007;
    const volatile int exponentArray[] = {0, 1, 0, 1, 0, 1, 0, 1};
    volatile int arrayLength = sizeof(exponentArray) / sizeof(exponentArray[0]);
    delay(2);
    volatile long long result = dumb_vulnerableExponentiation(base, exponentArray, arrayLength, modulo);
}
```

### Results

As presented in the begin for the encryption and decryption operation the key is the exponent, therefore discovering the exponent the RSA key is exposed.

Using the hardware previous mentioned it is possible to see the spectrum of power consumption in the osciloscope as presented in the **Figure* 14* and **Figure 15**

The periods which the voltage drops for a long time it means the bit `1`of the key is being processed, otherwise is the bit `0`.

Please, note that when the exponent is even there is one extra multiplication what makes the energy drop takes longer exposing key information.

**Video 2** shows the capturing of the key. Please to understand how to regulate the period and amplitude refer to the osciloscope manual.

![key_capture_using_shunt](https://github.com/lord-feistel/power_analysis/blob/main/images/key_capture_using_shunt.jpg)

**Figure 14** - Key capturing  

![showing_key](https://github.com/lord-feistel/power_analysis/blob/main/images/with_delay_02.jpg)

**Figure 15** - Exposing 0 and 1 of the key using oscilloscope 

[![Video 2: Key_capture](https://github.com/lord-feistel/power_analysis/blob/main/images/key_tumb.jpg)](https://youtu.be/MBZ1abtTN_k)


**Video 2** - Capturing the key with osciloscope.

Such a attack can be used in a scenario whic  the microcontroller is using an well-known library, however the firmware is locked not allowing the attacker to obtain the key directly from the memory.

This kind of attack also can be used against hardware.

### Conclusion

Implementing one's own RSA (Rivest-Shamir-Adleman) encryption system is highly discouraged due to several critical reasons, particularly vulnerability to sophisticated attacks like power analysis attacks. 

RSA encryption, while mathematically robust when implemented correctly, requires meticulous attention to detail in its implementation to ensure security

Even minor implementation flaws or oversights can inadvertently leak information about the private key, compromising the entire security of the system.

Furthermore, established cryptographic libraries and frameworks undergo rigorous scrutiny and testing by the security community, ensuring they are resilient against known attacks and vulnerabilities. Using these vetted libraries not only saves time and effort but also significantly reduces the risk of inadvertently introducing vulnerabilities into the system.

### References

1. Understanding Cryptography - Paar, C., & Pelzl, J. (2010). **Understanding Cryptography**. Springer.

2. Handbook of Applied Cryptography - Menezes, A. J., van Oorschot, P. C., & Vanstone, S. A. (1996). **Handbook of Applied Cryptography**. CRC Press.

3. Differential Power Analysis - Kocher, P., Jaffe, J., & Jun, B. (1999). **Differential Power Analysis**. Proceedings of CRYPTO '99, Lecture Notes in Computer Science, vol 1666. Springer, Berlin, Heidelberg. DOI: 10.1007/3-540-48405-1_25.

4. DS1102 Oscilloscope Datasheet - RIGOL Technologies, Inc. (2017). **DS1000E, DS1000D Series Digital Oscilloscope Datasheet**. Retrieved from [RIGOL Datasheet](https://beyondmeasure.rigoltech.com/acton/attachment/1579/f-03b8/1/-/-/-/-/DS1000E_DS1000D_DataSheet_EN.pdf)

5. Introductory Circuit Analysis - Boylestad, R. L. (2015). **Introductory Circuit Analysis** (13th ed.). Pearson.

6. Fundamentals of Electrical Circuits - Johnson, D., & Hilburn, J. L. (2013). **Fundamentals of Electrical Circuits**. McGraw-Hill Education.

7. Microelectronic Circuits - Sedra, A. S., & Smith, K. C. (2014). **Microelectronic Circuits** (7th ed.). Oxford University Press.
















