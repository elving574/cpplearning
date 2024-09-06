#include <iostream>
#include <vector>
#include <cstdlib>
#include <utility>
#include <cmath>
#include <algorithm>
#include <string>
#include <sstream>

typedef std::vector<std::pair<float,float>> layer;

void BTout(std::vector<float>);

int main(){
    std::vector<float> numList={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    //all numbers user entered will be stored in a sequence, and will later be displayed as a binary tree
    //below are simple code getting user input, copied from elvin's code
    while(1){
        int choice;
        std::cout << "\nMenu:\n";
        std::cout << "1. Add Element\n";
        std::cout << "2. View Tree (In Order)\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        switch (choice) {
            case 1:
                float value;
                std::cout << "Enter value to add: ";
                std::cin >> value;
                numList.push_back(value);
                break;
            case 2:
                BTout(numList);
                break;
            case 3:
                std::cout << "Exiting program.\n";
                std::exit(0);
            default:
                std::cout << "Invalid choice! Please try again.\n";
        }
    }
    return 1;
}

void BTout(std::vector<float> numList){
    int layerNum=0;
    for(int i=0,h=0;h<numList.size();i++){
        h+=std::pow(2,i);
        layerNum++;
    }//above is counculating the numbers of layers in the binary tree by the size of number sequence
    std::reverse(numList.begin(),numList.end());
    // the line above is reversing the number sequence so it is easier to pop from the bask of the vector to get data at the front of the sequence
    int largest=std::pow(2,layerNum);//getting the number of numbers at the bottom layer, which is the layer with the largest number of numbers
    for(int layer=0;layer<layerNum;layer++){
        std::cout<<std::endl;
        //there must be spaces between numbers to make it look nice, and the length of space is different between lines, the following code is for calculating it
        int layerEntity=std::pow(2,layer);//the number of numbers in the layer
        int spacesNum=largest/layerEntity/2*2;//algorithem for spaces, *2 at the end are just to make it looks better, can be changed
        std::string spaceGap(spacesNum,' ');//make string
        std::cout<<spaceGap;//move forward to center the numbers

        for (int ele=0;ele<layerEntity;ele++){
            //the following code will turn float into string then print it out
            //the purpose is to calculate the string length of float, so later we can subtract the space it took from the gap between numbers
            std::stringstream ftos;ftos<<numList.back();
            std::string eleStr(ftos.str());
            std::cout<<eleStr;
            numList.pop_back();
            if (!numList.size()){return;}
            std::cout<<spaceGap<<spaceGap<<std::string(eleStr.size(),'\b');//2 space gaps idk why i just tried and it worked, then subtract the space numbers took
        }
        //now the arrows to point to next layer just to make it look better
        std::cout<<std::endl;
        std::cout<<spaceGap;//move forward to center the numbers

        int slashSpace=spacesNum/4;//algo that calculates the half of the space between the root and the root's child at the next layer

        //the process of drawing arrows are simular to the process of output numbers, but at each position where numbers are outputed, 
        //it goes back a few spaces, output a left arrow, then go back, go forward a few spaces, output a right arrow, then keep going
        for (int ele=0;ele<layerEntity;ele++){
            std::cout<<std::string(slashSpace,'\b')<<'/'<<std::string(slashSpace,' ');
            std::cout<<std::string(slashSpace,' ')<<'\\'<<spaceGap<<spaceGap<<std::string(2+slashSpace,'\b');
        }
    }
}