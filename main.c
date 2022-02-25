#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

//создание строки с выделением памяти
char *newString(char *str) {
	//создание указателя, который хранит адрес выделенного пространства памяти
	//(размер: длина строки + 1 байт для символа окончания строки
	char *string = (char *) calloc(length(str) + 1, sizeof(char));
	//посимвольно копируем строку, переданную в функцию, в выделенную память	
	//***символ окончания строки присутствует изначально, т.к. использовалась функция calloc
	for (int i = 0; i < length(str); i++)
		string[i] = str[i];
	//возвращаем новую строку
	return string;
}

//вычисление длины строки
int length(char *str) {
	//создание переменной для вычисления длины строки
	int result = 0;
	//в цикле проходим с начала строки до момента, пока мы не дойдем до символа окончания строки
	//при каждой итерации цикла увеличиваем переменную result на 1
	for (int i = 0; str[i] != 0; i++)
		result++;
	//возращаем результат
	return result;
}

//функция обрезки строки
char *cut(char *str, int startChar, int countChar) {
	//вычисление количества вырезаемых символов. Если количество вырезаемых символов (countChar) превышает
	//количество символов в строке - то кладем в переменную size только количество затрагиваемых символов
	int size = (length(str) - startChar) < countChar ? (length(str) - startChar) : countChar;
	//выделяем память под новую строку + 1 символ окончания строки
	char *string = (char *) calloc(size + 1, sizeof(char));
	//копируем вырезаемые символы из старой строки в новую. В старой строке берем символы, начиная с startChar,
	//а в новую строку записываем символы, начиная с i - startChar, т.е. с нуля
	for(int i = startChar; i < startChar + countChar; i++)
		string[i - startChar] = str[i];
	//возвращаем обрезанную строку
	return string;
}

//функция для парсинга числа из строки
int parseInt(char *str) {
	int endPos = 0;
	for (int i = 0; i < length(str); i++) {
		if (str[i] >= 48 && str[i] <= 57)
			endPos = i;
	} 

	int result = 0;
	int mnozh = 1;
	for (int i = endPos; i >= 0; i--) {
		if (str[i] >= 48 && str[i] <= 57) {
			result += (str[i] - 48) * mnozh;
			mnozh *= 10;
		}
	}
	return result;
}

//функция вычисления длины самого большого слова в строке
int calcMaxWord(char *str) {
	int startPos = 0, endPos = 0, maxLength = 0;
	for (int i = 0; i < length(str) + 1; i++) {
		if (str[i] >= 32 && str[i] <= 64 || str[i] == '\0') {
			endPos = i;
			if (endPos - startPos > maxLength)
				maxLength = endPos - startPos;
			startPos = i;
			if ((str[i + 1] >= 'А' && str[i + 1] <= 'п') ||
				(str[i + 1] >= 'р' && str[i + 1] <= 'я') ||
				(str[i + 1] >= 'A' && str[i + 1] <= 'Z') ||
				(str[i + 1] >= 'a' && str[i + 1] <= 'z')) {
				startPos = i + 1;
			}
		}
	}
	return maxLength;
}

//функция поиска вхождения второй строки find в первую
int strInStr(char *str, char *find) {
	int result = 0;
	if (length(find) > length(str))
		return 0;
	for (int i = 0; i < length(str); i++) {
		if (str[i] == find[0]) {
			for (int j = 0; j < length(find); j++) {
				if (find[j] == str[i + j])
					result = 1;
				else {
					result = 0;
					break;
				}
			}
		}
	}
	return result;
}

int main(void) {
	setlocale(LC_ALL, "");

	char *string = newString("Привет, мир!");
	char *string2 = newString(" ");

	if (strInStr(string, string2) == 1)
		printf("true \n");
	else
		printf("false \n");

	return 0;
}