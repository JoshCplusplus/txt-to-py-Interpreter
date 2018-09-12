#include <iostream>
#include <unordered_map>
#include <fstream>

typedef std::string (*pfunc)(std::string);

std::string pyPrint(std::string s){
  std::string sentence;
  sentence = "print(\"" + s + "\")\n";
  return sentence;
}

void setup(std::unordered_map<std::string, pfunc> &m){
  m["print"] = pyPrint;
}

int main(){
  std::unordered_map<std::string, pfunc> funcMap;
  setup(funcMap);
  std::string word = "";
  std::string sentence = "";
  std::ifstream myfile;
  std::ofstream outfile;
  outfile.open("test.py");
  myfile.open("test.txt");
  if(myfile.is_open()){
    while(myfile >> word){
      if (funcMap.find(word) == funcMap.end()){
        outfile << word;
      }
      else{
        pfunc f = funcMap[word];
        while(myfile >> word){
          if(word == "end") break;
          if(sentence == "") sentence = word;
          else sentence = sentence + " " + word;
        }
        outfile << (*f)(sentence);
      }
    }
  }
  myfile.close();
  outfile.close();

}
