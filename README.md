[![Build status](https://ci.appveyor.com/api/projects/status/yjincxvqefv49p74?svg=true)](https://ci.appveyor.com/project/AntonGrigorev/kp)  
[![Build Status](https://travis-ci.com/AntonGrigorev/KP.svg?branch=main)](https://travis-ci.com/AntonGrigorev/KP) //main  
[![Build Status](https://travis-ci.com/AntonGrigorev/KP.svg?branch=test)](https://travis-ci.com/AntonGrigorev/KP) //test  
# KP Программа для распознания рукописных данных с последующей их обработкой в виде графиков 
##  Принцип работы ## 
При запуске программы появляется меню для выбора пути через проводник. Требуется выбрать фотографию в формате png с двумя векторами значений координат точек - первая строк X, вторая строка Y. После выбора фотографии с цифрами, если они удовлетворяют требованиями(цифры от 0 до 9, знаки . и -) и Tesseract верно их обработал, то появляется меню для построения графика по точкам. На выбор предлагается 4 масштаба графиков: линейный, логарифмический, полулогарифмический(по осям X и Y). После выбора, если это возможно (нельзя строить логарифмический график по отрицательным значениям), строится график по точкам на координатной плоскости.  
##  Выбор пути расположения файла ##  
![Image alt](https://github.com/AntonGrigorev/KP/raw/main/images/chose_path.png)   
##  Выбор типа графика ##  
![Image alt](https://github.com/AntonGrigorev/KP/raw/main/images/chose_graph.png)   
## Построение графиков по печатным данным ##  
![Image alt](https://github.com/AntonGrigorev/KP/raw/main/images/big_int.png)    
### Результат распознания ###  
![Image alt](https://github.com/AntonGrigorev/KP/raw/main/images/print_rec.png)  
## Графики ##
#### Линейный ####  
![Image alt](https://github.com/AntonGrigorev/KP/raw/main/images/lin.png) 
#### Логарифмический ####  
![Image alt](https://github.com/AntonGrigorev/KP/raw/main/images/log.png) 
#### Полулогарифмические ####  
![Image alt](https://github.com/AntonGrigorev/KP/raw/main/images/linlog.png)  
![Image alt](https://github.com/AntonGrigorev/KP/raw/main/images/loglin.png)  

### Результат распознания рукописных данных ###  
Рукописные данные нужно подавать через картинку, нарисованную в графическом редакторе (например, Paint).  
![Image alt](https://github.com/AntonGrigorev/KP/raw/main/images/hand.png)  
![Image alt](https://github.com/AntonGrigorev/KP/raw/main/images/hand_rec.png)  
