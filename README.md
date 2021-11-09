# IZ2_V26_Kalagaeva

[![Build Status](https://app.travis-ci.com/uglymarrow/IZ_Kalagaeva.svg?branch=IZ_2)](https://app.travis-ci.com/uglymarrow/IZ_Kalagaeva)
[![codecov](https://codecov.io/gh/uglymarrow/IZ_Kalagaeva/branch/main/graph/badge.svg?token=WYSHWVLD5C)](https://codecov.io/gh/uglymarrow/IZ_Kalagaeva)

Выполнение ИЗ№2 по курсу углубленное программирование С/С++

Вариант #26
Сравните и выведите в консоль время работы последовательного и параллельного с использованием нескольких процессов алгоритмов,
каждый из которых выделяет в динамической памяти числовой массив размером 100 Мб, заполненный положительными или отрицательными значениями температуры за день,
после чего выполняет поиск времени, когда произошел самый резкий положительный скачок температуры.

На что необходимо обратить внимание:
- при разработке обеих библиотек стоит делать общий интерфейс, не раскрывая особенностей реализации;
- библиотеки должны быть взаимозаменяемыми - конкретная реализация (последовательная/параллельная) - использоваться в зависимости от конфигурации сборки;
- юнит-тесты должны быть реализованы для обеих реализаций (последовательной/параллельной). Покрытие тестами должно быть максимально возможным;
- должны присутствовать стресс-тесты. Они могут быть реализованы внешним образом, запуская две разные программы - одну со статической библиотекой с последовательной реализацией, вторую - с динамической библиотекой с параллельной реализацией, и сравнивая их выводы друг с другом.
- для организации ввода/вывода больших данных полезно работать с файлами, а в программе - предусмотреть работу с универсальными потоками входных/выходных данных (или хотя бы перенаправлять ввод/вывод на уровне их запуска)
- если в задании сказано, что программа должна обрабатывать файлы объёмом 100 Мб – это лишь ориентир, на которых программа точно должна работать, и на котором имеет смысл делать замеры производительности и эффективности алгоритмов. Поэтому тесты на такой объём должны быть. Однако сама программа должна уметь работать с произвольными размерами входных данных
- измерение времени должно осуществляться внешним образом, а не внутри кода библиотек. При этом необходимо делать несколько замеров и усреднять. Стоит помнить о том, что clock() в многопоточных приложениях работает не так, как ожидается.
- внедрить CI: форматтеры,  статические и динамические анализаторы кода, тесты с запуском valgrind и санитайзеров, генерация html-отчётов о покрытии кода тестами добиться прохождения всех проверок перед отправкой на ревью

Замечания:
1. Нет обработки ошибок стандартных функций.
2. main не нужно нагружать бизнес-логикой. main это точка входа для вызова других функций (подпрограмм) назначение которых должно максимально отражать их именование (сигнатура).
3. Дублирование кода. Особо часто это происходит в местах выделения и освобождения памяти.
4. Для указания размера чего-то в байтах используйте size_t, а не int.
5. В тех случаях, когда оригинальны массив строк должен остаться неизменным после работы функции, его нужно передавать через указатель на константу. Т.о. между вызывающей стороной и вызываемой функцией заключается контракт о том, что данные передаваемого массива изменены не будут.
6. Использование одного и того же указателя в качестве передаваемого и возвращаемого значения p = realloc(p,.. ); В случае ошибки p будет перезаписан на NULL, что приведет к утечке памяти.
8. Не используйте scanf(“%s” без ограничения размера записи. Это может привести к переполнению буфера. https://rules.sonarsource.com/c/RSPEC-1079
9. Использование exit() является плохой практикой, это может приводить к тому, что ресурсы системы или других используемых программ корректно освобождены не будут.
10. Если переменная не предполагает изменения своего значения то обязательно используйте спецификатор const.
11. В функциях проверяйте значение передаваемых аргументов, например, указатели перед их разыменованием.
12. В языке C используется snake_case написания кода https://en.wikipedia.org/wiki/Snake_case, а не camelCase
14. Вместо поэлементного копирования элементов в цикле в другой массив старайтесь использовать memcpy
16. Операция чтения строк из стандартного ввода. Работа с динамической памятью, выделение или освобождение — это дорогостоящие операции, нужно стараться минимизировать их количество.
Например:
Выделить динамическую память под всю строку размера N (arr), например, 1024 байта.
Прочитать чанк данных фиксированного размера и записать его в массив (arr) смещая на каждой итерации адрес записи на величину чанка. Либо записывать в автоматический буффер chank[64] (старайтесь не использовать массивы переменной длинны https://en.wikipedia.org/wiki/Variable-length_array) с последующим копированием в массив arr.
В случае если, динамический массив заполнился нужно переаллоцировать память (realloc)
В случае если встретился чанк заканчивающий строку или EOF, нужно обрезать зарезервированную память, если в этом есть необходимость и вернуть строку.
17. Операция чтения строк из стандартного ввода. Отдавайте предпочтение построчному (блочному) чтению (fgets, scanf, fscanf), нежели посимвольному (getchar, scanf("%c", c), для решения задачи чтения строк из стандартного ввода.
18. Делегирование ответственности за очищение памяти вызываемой функции из названия которой совершенно не очевидно подобное поведение (find_man, scan_array и прочее).
19. Проверяйте программу cppcheck’ом
cppcheck --inconclusive --enable=all --language=c <file.c>
20. Используйте инструменты для форматирования исходного кода, например, clang-format –style=Google
21. Выделение 0 байт через *alloc методы - https://wiki.sei.cmu.edu/confluence/display/c/MEM04-C.+Beware+of+zero-length+allocations

Необходимо настроить CI на автоматические проверки при появлении новой версии Merge Request. Из форматтеров и анализаторов требуется поддержать clang-format, clang-tidy, cpplint, cppcheck, scan-build, fbinfer. Тесты должны запускаться с санитайзерами (memory, address, undefined, thread) и под valgrind. Также должно замеряться покрытие кода тестами, и в артефактах размещаться html-отчёт с возможностью перехода к каждому исходному файлу в отдельности. Это будет свидетельствовать о том, что ваш код действительно удовлетворяет некоторым базовым критериям качества, и вы готовы к прохождению ревью. Важно, что весь код программы должен быть в Pull Request (например, не должно быть такого, что весь код в основной ветке репозитория, а в Pull Request добавляется пробел...). Также в Pull Request (в комментариях или в файле с программой) должно быть приведено условие задачи.

- Pipe example https://github.com/leshiy1295/technopark_c_c_plus_plus/blob/master/examples/lecture2/010_pipe.c
