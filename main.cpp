// Take input colour, output colour, numSteps , and a message.
// Transform input to output in numSteps steps.
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <iomanip>
#include <fstream>
int main(int argc, char* argv[]){
    char msgArray[256];
    bool DEBUG = false;
    int red1, green1, blue1, red2, green2, blue2;
    int numSteps = 10;
    std::string color1, color2, strSteps, message;
    std::fstream file;
    file.open("output.txt",std::fstream::in|std::fstream::out|std::fstream::trunc);

    if (argc > 1) {
            DEBUG = true;
            message = "Taxi: ON, Res: ";
            message += argv[1];
            red1 = 0x33;
            red2 = 0xAA;
            green1 = 0xFF;
            green2 = 0xFF;
            blue1 = 0xFF;
            blue2 = 0xFF;
    }
//TODO: Input validation.
if( !DEBUG){
  std::cout << "What's the first color?\n";
  std::cin >> color1;
  std::cout << "\nAnd the second color?\n";
  std::cin >> color2;
  std::cout << "\nHow many steps?\n";
  std::cin >> strSteps;
  std::cout << "And what's the message?\n";
  while (message.length() == 0){
  std::cin.getline(msgArray,256);
  message = msgArray;
  }
  try {
  numSteps = stoi(strSteps);
  } catch (const std::invalid_argument& ia) {
      numSteps = 10;
  }

  try{
      red1 = stoi(color1.substr(0,2),0,16);
      red2 = stoi(color2.substr(0,2),0,16);
      green1 = stoi(color1.substr(2,2),0,16);
      green2 = stoi(color2.substr(2,2),0,16);
      blue1 = stoi(color1.substr(4,2),0,16);
      blue2 = stoi(color2.substr(4,2),0,16);
  } catch (const std::invalid_argument& ia) {
      std::cout << "Error parsing color codes! Please type just six hex digits.\n";
      return 1;
  }
}
  int deltaRed = red1 - red2;
  int deltaGreen = green1 - green2;
  int deltaBlue = blue1 - blue2;

  double stepRed = deltaRed / numSteps;
  double stepGreen = deltaGreen / numSteps;
  double stepBlue = deltaBlue / numSteps;

  double msgStep = (double)message.length() / (double)numSteps;
  //std::cout << "Message length : " << message.length() << " and numSteps " << numSteps << "give msgStep of " << msgStep << std::endl;
  if (numSteps > message.length()){
        numSteps = message.length();
        msgStep = 1;
  }

  double curRed, curGreen, curBlue, curMsg = 0;
  int curInt = 0;

  std::string msgOut;
  std::cout << std::resetiosflags(std::ios_base::dec) << std::setiosflags(std::ios_base::hex|std::ios_base::uppercase|std::ios_base::right) << std::setfill('0') << std::setw(3);
  file << std::resetiosflags(std::ios_base::dec) << std::setiosflags(std::ios_base::hex|std::ios_base::uppercase|std::ios_base::right) << std::setfill('0') << std::setw(3);

  int prevstep = 0;
  int previdx = 0;

  for (int i = 0; i < numSteps; i++){
  msgOut = message.substr(previdx, std::max((msgStep * i) - previdx,std::floor(1)));
  previdx += std::max((msgStep * i) - previdx, std::floor(1));
  //std::cout << "msgOut is: " << msgOut << ". floor(curMsg) is " << std::floor(curMsg) << " and msgStep is " << msgStep << std::endl;
  //std::cout << red1 << green1 << blue1 << std::endl;
  std::cout << "%^#";// << std::uppercase << std::hex << red1 << std::uppercase << std::hex << green1 << std::uppercase << std::hex << blue1 << "%^";
  file << "%^#";
  std::cout << std::setw(2) << red1;
  file << std::setw(2) << red1;
  std::cout << std::setw(2) << green1;
  file << std::setw(2) << green1;
  std::cout << std::setw(2) << blue1;
  file << std::setw(2) << blue1;
  std::cout << "%^";
  file << "%^";
  std::cout << msgOut;
  file << msgOut;

  std::cout << "%^RESET%^";
  file << "%^RESET%^";
  if (DEBUG){
        //std::cout << "  curMsg: " << curMsg << " curInt: "<< curInt << " " <<  std::max(std::floor(curMsg)-curInt,std::floor(1)) << std::endl;
  }
  red1 -= stepRed;
  green1 -= stepGreen;
  blue1 -= stepBlue;
  curMsg += msgStep;
  curInt += prevstep;
  if (curMsg > message.length()) {
        curMsg = message.length();
        }
  if (curInt > message.length()) {
        curInt = message.length();
        }
  }
  msgOut = message.substr(previdx, message.length() - previdx);
  std::cout << "%^#";
  file << "%^#";
  std::cout << std::setw(2) << red2;
  file << std::setw(2) << red2;
  std::cout << std::setw(2) << green2;
  file << std::setw(2) << green2;
  std::cout << std::setw(2) << blue2;
  file << std::setw(2) << blue2;
  std::cout << "%^";
  file << "%^";
  std::cout << msgOut;
  file << msgOut;
  std::cout << "%^RESET%^";
  file << "%^RESET%^";
  file.close();


   return 0;
   }
