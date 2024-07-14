# Quick course in number theory for RSA

  - [Basics of Number Theory](#basics-of-number-theory)
    - [Modulo Operation](#modulo-operation)
    - [Divisibility](#divisibility)
    - [Modular Arithmetic](#modular-arithmetic)
    - [Prime Numbers](#prime-numbers)
    - [Greatest Common Divisor](#greatest-common-divisor)
    - [Co-primes](#co-primes)
    - [Euler's Totient Function (Phi Function)](#eulers-totient-function-phi-function)

---

## Basics of Number Theory

### Modulo Operation

This operation is well known by programmers:

   ```a = 7 % 2```  

If you are not familiar with this operation, don't worry, basically it means that `a` is the remainder of the integer division of `7` by `2`, in this case `1`. 

Please note that although it's possible to divide `7` by `2` in real numbers resulting in `3.5`, we are interested in the integer division ( euclidean division)  which is the division containing a remainder.  

To be divisible a integer division should result in a remainder ( rest ) equal to 0 ( zero ), thus ``` 7 / 2 = 3```  and```  remainder = 1```  so it’s not divisible by `2`.

**Example I** 

Evaluate a = 7 % 2 

**Answer:**

7 ÷ 2 = 3 and reminder = 0. 
We can express it as 7 ≡ 1 mod 3, the ≡ symbol means equivalence

**Example II**

Evaluate a = 7 % 2 ;

**Answer:**

 ```37 ÷ 112 = 0 ``` and  ```reminder = 37 ``` . 
We can express it as 37 ≡ 37 mod 112

### Divisibility

If ```a ÷ b = c``` for ```b > 0``` and ```remainder = 0```  we say that a is divisible by `b` , also, we say `b` is an   `a` divisor.

**Example :** 
Check if 28 divisible by 2

28÷ 2 = 14 and reminder = 0 or 28 ≡ 0 mod 2

### Modular arithmetic

The modulo supports a range of arithmetic operations following the examples which also show the properties. They are almost strait forward, unless division and inversion

**addition**

```( 120 % 12 + 13 % 12 ) % 12 = ( 120 + 13) % 12 = ( 133) % 12 = 1 ≡ 1 mod 12```

**subtraction**

```( 11 % 5 - 1 % 5 ) % 5 = ( 11 - 1) %5 = 10 % 5 ≡ 0 mod 5```

**multiplication**

```( 7 % 12 * 2 % 12 ) % 12 = ( 7 * 2 ) % 12 = 14 % 12 ≡ 2 mod 12```

**Modulo Inversion**

```b is inverse of a in a mod c if ( a * b ) ≡ 1 mod c```

**Example I**

`9` is the modular inverse of `3` mod `26` because  ```9 * 3 = 27 ``` and  ```27 ≡ 1 mod 26 ```

**Example II**

```122``` is the modular inverse of ```3454 mod 283``` because ```122 * 3454 = 421388``` and ```421388 ≡ 1 mod 283```

Some authors represent the modular inversion as a * a<sup>-1</sup> = 1 mod c because on regular arithmetic
the inverse of a is a<sup>-1</sup> what is the same of 1/a
If you are curious about more cases you can try others values here. 
In the future it will be discussed how the modular inverse is obtained.

### Prime numbers

Prime numbers are numbers which are divisible only by 1 and itself, e.g :

**Example I**

Is 7 a prime number ?

Answer : It is because it can only be divided by 1 and 7 ( on those divisions the remainder is zero)

**Example II**

Is 9 a prime number ?

It is not prime once it is divided by 3 since the remainder of 9 / 3 is equal to 0 ( zero ).

### Greatest Common Divisor

Imagine two positive integers y and z

if x is the biggest number which y and z are divisible , then this is the gcd ( greatest common divisor) between y and z is

**Example**

what is the gcd between `18` and `15` ?

numbers which divide `18` : {`1, 2 ,3 ,6 , 9, 18` }

numbers which divide `15` : {`1, 3 ,5 ,15` }

The numbers which commonly divides `15` and 18 : {`1, 3`} , therefore the gcd is `3`  since is the biggest number which divide both of them.

### Co-primes

Two numbers are co-prime when the gcd between them is 1, simple like that.

**Example I**

Are 18 and 15 co-primes ?

Answer: No because the gcd between 18 and 15 is 3

**Example II**

Are 9 and 7 co-primes ?

**Answer:** 
Yes, the gcd between 9 and 7 is 1. Please, note that although 9 is not prime as previously demonstrated he is co-prime with 7.

### Euler's Totient Function (Phi Function)

The Euler's Totient function, denoted as **φ(n)**, counts the number of integers up to n that are co-prime with n. In other words, it calculates the count of integers ```k ``` such that  ```1 ≤ k ≤ n ``` and **GCD(k, n) = 1**.

#### Example

Calculate **φ(12**):

The numbers up to  ```12 ``` are  ```{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12} ```.

Among them, the co-primes with `12` (i.e., **GCD(k, 12) = 1** ) are  ```{1, 5, 7, 11} ```. Thus, **φ(12) = 4**.

The Euler's Totient function plays a crucial role in various number theory applications, including **RSA** encryption, where it is used to calculate the public and private keys.






