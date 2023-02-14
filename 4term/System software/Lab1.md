# Лабораторна работа #1
---

## Общие задания
1. Подсчитать колличество файлов в подкаталоге
  - Для перехода в нужный каталог вводим cd <Путь к каталогу>
  - Вводим ls -l для просмотра содержимого подкаталога
  
  ```
  chujko@ltsp181:~$ cd /home/public/
chujko@ltsp181:/home/public$ ls -l
итого 1104
drwxr-xr-x  2 1000  1000   4096 фев  8  2010 Altera
drwxr-xr-x  3 1000  1000   4096 ноя 29  2010 Altera-Linux
drwxr-xr-x  4 1000  1000   4096 мая 27  2011 Altera-Linux-11
-rw-r--r--  1 1000  1000  19643 апр 19  2021 AP_51-8.odt
-rw-r--r--  1 1000  1000  19014 мая 17  2021 AP_54-11.odt
-rw-r--r--  1 1000  1000  21941 мая 18  2021 AP_56-13.odt
-rw-r--r--  1 1000  1000  18875 июн  9  2021 AP_59-16.odt
-rw-r--r--  1 1000  1000  19287 июн  9  2021 AP_60-17.odt
-rw-r--r--  1 1000  1000  19784 фев 16  2022 AP_62-19.odt
-rw-r--r--  1 1000  1000  21072 фев 16  2022 AP_63-20.odt
-rw-r--r--  1 1000  1000  21299 фев 16  2022 AP_64-21.odt
-rw-r--r--  1 1000  1000  18787 фев 16  2022 AP_65-22.odt
-rw-r--r--  1 1000  1000  23586 фев 16  2022 AP_66-23.odt
-rw-r--r--  1 1000  1000  31921 фев 16  2022 AP_67-24.odt
-rw-r--r--  1 1000  1000  26657 фев 16  2022 AP_68-25.odt
-rw-r--r--  1 1000  1000  32401 фев 16  2022 AP_69-26.odt
-rw-r--r--  1 1000  1000  23021 фев 16  2022 AP_70-27.odt
-rw-r--r--  1 1000  1000  21737 фев 16  2022 AP_71-28.odt
-rw-r--r--  1 1000  1000  20698 фев 16  2022 AP_72-29.odt
-rw-r--r--  1 1000  1000  19242 сен 13  2021 AP_75-32.odt
-rw-r--r--  1 1000  1000  20439 окт 18  2021 AP_79-36.odt
-rw-rw-rw-  1 1000  1000  21213 окт 26  2021 AP_82-39.odt
-rw-r--r--  1 1000  1000  20312 дек 17  2021 AP_84-41.odt
-rw-r--r--  1 1000  1000  21201 янв 18  2022 AP_86-2.odt
-rw-r--r--  1 root root   22746 окт 11 13:09 AP_96-12.odt
drwxr-xr-x  4 root root    4096 сен 11  2020 Arduino
drwxr-xr-x  9 1000  1000   4096 сен  3  2021 arduino-1.8.16
drwxr-xr-x  2 root root    4096 дек 17  2021 arduino.tools
drwxr-xr-x  5 root root    4096 фев 16  2021 Assembler
-rw-r--r--  1 1000  1000 178618 мар 16  2006 bakalawr.pdf
drwxrwxr-x  7 root staff   4096 июн 10  2010 Books
drwxr-xr-x 20 root root    4096 мая  6  2008 Cel.extras
-rwxr-xr-x  1 root root    2517 мар 28  2012 db_student.sql
drwxr-xr-x  2 1000  1000   4096 мар 29  2011 Debian-60r1
drwxr-xr-x  2 root root    4096 фев 20  2016 Debian-8.0
-rw-r--r--  1 1000  1000 276310 мар 16  2006 diplom.pdf
drwxr-xr-x  2 1000  1000   4096 апр 12  2011 Efremov-Quartus
drwxr-xr-x  3 1000  1000   4096 мая 31  2011 Fonts.old
drwxr-xr-x  3 1000  1000   4096 дек 27  2013 Humor
drwxr-xr-x 16 1010 users   4096 мар  2  2017 laba_bd
drwxr-xr-x  8 1000  1000   4096 сен 24  2012 MatLab6.5
drwxr-xr-x  2 1000  1000   4096 ноя 22  2007 Octave-doc
drwxr-xr-x  5 1000 staff   4096 фев 19  2019 OS
drwxrwxrwx  6 1000  1000   4096 апр 15  2010 pc
drwxr-xr-x 49 1000  1000   4096 окт 28  2019 Photos
drwxr-xr-x  2 1000  1000   4096 апр 17  2007 Pictures
drwxr-xr-x  4 1000  1000   4096 сен 10  2021 ProgtMikr
drwxr-xr-x  2 1000  1000   4096 окт 17  2020 SovremennyeProblemy
drwxr-xr-x  7 1000 staff   4096 фев  8 11:38 SPO
drwxr-xr-x  3 1000  1000   4096 мар 19  2018 TehnologiiInternet
drwxr-xr-x  2 1000  1000   4096 мар 27  2021 tmp
drwxr-xr-x  5 1000  1000   4096 фев 25  2017 TTF-Fonts-free
drwxr-xr-x  4 1000  1000   4096 сен 22  2007 UDK
drwxr-xr-x  3 1000  1000   4096 дек  6  2016 Unicode
drwxr-xr-x  3 1000  1000   4096 мар  6  2019 Vim.docs
drwxr-xr-x  2 1000  1000   4096 апр 15  2010 VirtualBox-for-Debian4.0
drwxr-xr-x  3 1000  1000   4096 сен 20  2007 Web.offline
drwxr-xr-x  2 root root    4096 мар  6  2008 WIN

  ```
  3. Вычислить суммарный обьем, занимаемый файлами в подкаталоге
    - Вводим комманду ```ls -l | awk '{size += $5} END {print size}'```
    - Получаем обьем каталога 3669380