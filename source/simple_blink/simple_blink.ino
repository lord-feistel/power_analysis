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

