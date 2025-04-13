#include <stdio.h>
#include <string.h>
#include <ctype.h>  

#define MAX_SENTENCE 1000

// Fonksiyon prototipi
int countWord(const char *sentence);

int main() {
    while (1) {
    char sentence[MAX_SENTENCE];

    printf("Enter a sentence: ");
    fgets(sentence, MAX_SENTENCE, stdin); // Boşluklu giriş için fgets kullanıyoruz

    // Yeni satır karakterini kaldır (fgets bırakıyor)
    size_t len = strlen(sentence);
    if (len > 0 && sentence[len - 1] == '\n') {
        sentence[len - 1] = ' ';
    }

    // Kelime sayısını hesapla
    int count = countWord(sentence);

    printf("Number of counted words: %d\n", count); }

    return 0;
}


int countWord(const char *sentence)
{
    int counter = 0;
    int len = strlen(sentence);
    
    for (int i = 0; i < len; i++)
    {
        if ((i > 0 && isspace(sentence[i]) && isalnum(sentence[i-1])) || i > 0 && (isspace(sentence[i]) && ispunct(sentence[i-1])))
        {
            counter++;
        }
    }

    return counter;
}



// TEST CASE:
// Bugün hava çok güzel.
// Merhaba    dünya!  Nasılsın   bugün?
    
// Merhaba
// Merhaba, dünya! Bu bir test cümlesidir.
// Bugün dişari çikacağim.   
// [Enter]



// TODO:
// En uzun kelimeyi bul
// Cümledeki kelimeleri alt alta yaz.
// Noktalama işaretlerini silip kelime say
// Küçük büyük harf normalleştirme



// CHATGPT KOD
// #include <stdio.h>
// #include <string.h>
// #include <ctype.h> // isspace()

// int main() {
//     char cumle[1000];
//     int i = 0, kelime_sayisi = 0;
//     int in_kelime = 0;

//     printf("Bir cümle girin: ");
//     fgets(cumle, sizeof(cumle), stdin); // kullanıcıdan satır al

//     while (cumle[i] != '\0') {
//         // Eğer karakter boşluk, tab veya yeni satır ise kelime içinde değiliz
//         if (isspace(cumle[i])) {
//             in_kelime = 0;
//         } else if (in_kelime == 0) {
//             // Boşluktan kelimeye geçiş olursa kelime sayısını artır
//             kelime_sayisi++;
//             in_kelime = 1;
//         }
//         i++;
//     }

//     printf("Toplam kelime sayısı: %d\n", kelime_sayisi);

//     return 0;
// }