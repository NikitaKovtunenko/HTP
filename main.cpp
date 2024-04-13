#include <iostream>
#include <array>
#include <algorithm>
#include <bitset>
//Напишите функцию, которая инвертирует только выбранные
//биты в участке памяти, заданном указателем и длиной в байтах.

using Function = void (*)(uint8_t*,uint8_t*,size_t*,size_t);
void SetRightToLeft(uint8_t*, uint8_t* , size_t* , size_t );
void SetLeftToRight(uint8_t* , uint8_t* , size_t* , size_t );


void BitInverter(void * ptrBegin, size_t size,Function SetBits = SetRightToLeft ){

    if(!ptrBegin){
        return;
    }

    size_t numOfBits = 0;
    std::cout << "Enter num of bits for the invert. First bit == 1" << '\n';
    std::cin >> numOfBits;

    if(numOfBits <= 0)
        return;

    size_t * array = new size_t [numOfBits];

    size_t lengthInBits = size * 8;

    for (size_t i = 0; i < numOfBits; ++i) {
        size_t num  =0;
        std::cin >> num;

        if( num > 0 && num <= lengthInBits)
        {
                array[i] = num;
                array[i]--;
        }

    }

    std::sort(array,array + numOfBits);

    uint8_t* ptrFirst = static_cast<uint8_t *> (ptrBegin);
    uint8_t* ptrEnd =  ptrFirst + size -1;

    SetBits(ptrFirst,ptrEnd,array,numOfBits);

    delete[] array;
}

void SetRightToLeft(uint8_t*, uint8_t* end, size_t* array, size_t size)
{
    size_t count = 1;
    for (size_t i = 0; i < size; ++i) {

        if(array[i] > count * 8 ) {
            count++;
            end--;
            i--;
            continue;
        }

        *end ^= (1 << (array[i] % 8));
    }
}

void SetLeftToRight(uint8_t* begin, uint8_t* , size_t* array, size_t size)
{
    size_t count = 1;

    for (size_t i = 0; i < size; ++i) {

        if(array[i] >= count * 8 ) {
            count++;
            begin++;
            i--;
            continue;
        }

        *begin ^= (1 <<  7 - array[i]  % 8  );

    }
}

void printBinary(void* num , size_t size) {
    uint8_t* number = static_cast<uint8_t*>(num);

    for (int i = 0; i < size; ++i) {
        std::bitset<8> ff(*number);
        std::cout << ff <<  ' ';
         number++;

    }
    std::cout << std::endl;
}

int main() {

    int num = -1;
    std::cout << std::endl;
   // int array[5] = {-1,-1,-1,-1,-1};
    int64_t array = -1;
    printBinary(&array,sizeof(array));
    BitInverter(&array,sizeof(array));
    printBinary(&array,sizeof(array));

    return 0;
}
