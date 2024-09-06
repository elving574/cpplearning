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
    int largest=std::pow(2,layerNum);//getting the largest 
    for(int layer=0;layer<layerNum;layer++){
        std::cout<<std::endl;
        //gap config
        int layerEntity=std::pow(2,layer);
        int spacesNum=largest/layerEntity/2*2;
        std::string spaceGap(spacesNum,' ');
        std::cout<<spaceGap;

        for (int ele=0;ele<layerEntity;ele++){
            std::stringstream ftos;ftos<<numList.back();
            std::string eleStr(ftos.str());
            std::cout<<eleStr;
            numList.pop_back();
            if (!numList.size()){return;}
            std::cout<<spaceGap<<spaceGap<<std::string(eleStr.size(),'\b');
        }
        std::cout<<std::endl;
        std::cout<<spaceGap;

        int slashSpace=spacesNum/4;
        for (int ele=0;ele<layerEntity;ele++){
            std::cout<<std::string(slashSpace,'\b')<<'/'<<std::string(slashSpace,' ');
            std::cout<<std::string(slashSpace,' ')<<'\\'<<spaceGap<<spaceGap<<std::string(2+slashSpace,'\b');
        }
    }
}