# binedit #

This is a extremely simple and dumb utility to replace strings in a binary file. I know it's a rare thing to do, but sometimes you just need it. 
Наверняка есть что аналогичное, и даже лучше, но мне лень было гуглить и тестить, когда я за то же время могу себе сам нужное сделать. 

В общем, вдруг кому понадобиться: тулза, чтобы менять в бинарниках одну строку на другую.



Тупо грузит заданный файл и заменяет в нём исходную строку на целевую. Строки, понятное дело, должны быть одинаковой длины. Во-первых, потому что утиль тупая, во-вторых, потому что в бинарниках лишний раз лучше ничего никуда не двигать.

### making ###

Just compile it. There is nothing but pure C runtime.

### running ###

`binedit -file=<filename> -src=<src string> -dst=<dest string>`

I know, the syntax is not usual unix, I'll fix it. May be.

### limitations ###

`src string` and `dest string` must be the same length. Because it's a really dump utility and you better not play with data lengths in a binary.

### license ###

This software is released under the WTFPL.