#include <iostream>
#include <unordered_map>
#include <fstream>

typedef std::string (*pfunc)(std::ifstream &infile);


std::string pyEqual(std::ifstream &infile){
  return " = ";
}

std::string pyIf(std::ifstream &infile){
  std::string sentence;
  std::string word;
}

std::string pyString(std::ifstream &infile){
  std::string sentence;
  std::string word;
  while(infile >> word){
    if(word == "end") break;
    else sentence = sentence + word + " ";
  }
  sentence.resize(sentence.size()-1);
  return "\"" + sentence + "\"";
}

std::string pyPrint(std::ifstream &infile){
  std::string sentence = "print(\"";
  std::string word;
  while(infile >> word){
    if(word == "end") break;
    if(sentence == "print(\"") sentence += word;
    else sentence = sentence + " " + word;
  }
  return sentence + "\")\n";
}

void setup(std::unordered_map<std::string, pfunc> &m){
  m["print"] = pyPrint;
  m["equals"] = pyEqual;
  m["if"] = pyIf;
  m["string"] = pyString;
}

int main(){
  std::unordered_map<std::string, pfunc> funcMap;
  setup(funcMap);
  std::string word = "";
  std::string sentence = "";
  std::ifstream infile;
  std::ofstream outfile;
  outfile.open("test.py");
  infile.open("test.txt");
  if(infile.is_open()){
    while(infile >> word){
      auto key = funcMap.find(word);
      if (key == funcMap.end()){
        outfile << word;
      }
      else{
        outfile << (*(key->second))(infile);
      }
    }

  infile.close();
  outfile.close();
  }
}
