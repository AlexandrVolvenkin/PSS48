//-----------------------------------------------------------------------------------------------------
//  Source      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------------------
#ifndef CBUZZER_H
#define CBUZZER_H


#include <stdint.h>

//-----------------------------------------------------------------------------------------------------
class CBuzzer
{
    public:
        CBuzzer();
        virtual ~CBuzzer();
        static void Init(void);
        static void LowOn(void);
        static void HighOn(void);
        static void Off(void);

    protected:
    private:

};

//-----------------------------------------------------------------------------------------------------
#endif // CBUZZER_H
