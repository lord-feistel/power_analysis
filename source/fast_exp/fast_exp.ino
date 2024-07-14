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

volatile long long fastExponentiation(volatile long long base, volatile long long exponent, volatile long long modulo) {
    volatile long long result = 1;
    base %= modulo;

    while (exponent > 0) {
        if (exponent & 1) {
            result = (result * base) % modulo;
        }
        base = (base * base) % modulo;
        exponent >>= 1;
    }

    return result;
}

void setup() {
}

void loop() {
    volatile long long base = 3;
    volatile long long exponent = 5555555;
    volatile long long modulo = 1000000007;
    delay(2);
    volatile long long result = fastExponentiation(base, exponent, modulo);
    delay(2);
}
