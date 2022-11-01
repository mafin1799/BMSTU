package main

import "fmt"

func encrypt(message string, key string) string {
	var encrypt []rune
	var arr []string

	sizeMessage := len(message)
	sizeKey := len(key)
	resDEL := sizeMessage / sizeKey
	//ostDEL := sizeMessage / sizeKey
	for t := 0; t < resDEL*sizeKey; t += sizeKey {
		arr = append(arr, message[t:sizeKey+t])
	}
	arr = append(arr, message[resDEL*sizeKey:sizeMessage])
	fmt.Println(arr)
	for i := 0; i < len(arr); i++ {
		for j := 0; j < len(arr[i]); j++ {
			K := key[j]
			T := arr[i][j]
			R := T + K - 96

			if R >= 'a' && R <= 'z' {
				encrypt = append(encrypt, rune(R))
			} else if R >= 'A' && R <= 'Z' {
				encrypt = append(encrypt, rune(R))
			} else if R < 97 || R > 122 {
				encrypt = append(encrypt, rune(R-26))
			}
		}
	}
	return string(encrypt)
}

func decrypt(message string, key string) string {
	var encrypt []rune
	var arr []string

	sizeMessage := len(message)
	sizeKey := len(key)
	resDEL := sizeMessage / sizeKey
	for t := 0; t < resDEL*sizeKey; t += sizeKey {
		arr = append(arr, message[t:sizeKey+t])
	}
	arr = append(arr, message[resDEL*sizeKey:sizeMessage])
	fmt.Println(arr)

	for i := 0; i < len(arr); i++ {
		for j := 0; j < len(arr[i]); j++ {
			K := key[j]
			T := arr[i][j]
			R := T - K + 96

			if arr[i][j] >= 'a' && arr[i][j] <= 'z' && R >= 'a' && R <= 'z' {
				encrypt = append(encrypt, rune(R))
			} else if arr[i][j] >= 'A' && arr[i][j] <= 'Z' && R >= 'A' && R <= 'Z' {
				encrypt = append(encrypt, rune(R))
			} else if arr[i][j] >= 'A' && arr[i][j] <= 'Z' && R >= 'a' && R <= 'z' {
				encrypt = append(encrypt, rune(R-26))
			} else if arr[i][j] >= 'a' && arr[i][j] <= 'z' && R >= 'A' && R <= 'Z' {
				encrypt = append(encrypt, rune(R+26))
			} else if arr[i][j] >= 'a' && arr[i][j] <= 'z' && R > 'Z' && R < 'a' {
				encrypt = append(encrypt, rune(R+26))
			}
		}
	}
	return string(encrypt)
}

func main() {
	fmt.Println(encrypt("Crusader", "bow"))
	fmt.Println(decrypt("Egrupagg", "bow"))
}
