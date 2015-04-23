#include <p32xxxx.h>

int main(void){
    setup(); //configuration

    while(1){
        loop(); //if USER button pushed, toggle LED
    }
}
