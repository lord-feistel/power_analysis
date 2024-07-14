/*
 *
 * Copyright (c) 2022 
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>. 
 * 
 * Author : Antonio ( Lord Feistel)
 *
 * e-mail : jr.overhead@gmail.com
 * e-mail : lord.feistel@gmail.com
 * 
 */


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
// It can be inserted to improve visualization
//        delayMicroseconds(100);
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
