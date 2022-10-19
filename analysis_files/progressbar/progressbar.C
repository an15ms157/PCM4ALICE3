#include <iostream>
#include "./progressbar.h"

void progressbar() {
  ProgressBar bar1(100); 
    for (int i = 1; i < 100; i++) {    
         bar1.progress(i+1);
    }  
}