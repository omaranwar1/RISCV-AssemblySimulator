//
//  main.cpp
//  Assembly_project
//
//  Created by Amal Fouda on 10/11/2023.
//

#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>
#include <bitset>

using namespace std;

vector<string>R_type = {"add", "sub", "sll", "slt", "sltu", "xor", "srl", "sra", "or", "and"};
vector<string>I_type = {"addi", "slti", "sltiu", "xori", "ori", "andi"};
vector<string>I_type2={"lb","lh","lw","lbu","lhu"};
vector<string>B_type={"beq","bne","blt","bge","bltu","bgeu"};
vector<string>S_type={"sw","sh","sb"};
vector<string>jump_link={"jalr"};
vector<string>jump2={"jal"};
vector<string>shifiting={"slli","srli","srai"};
vector<string>lower_upperImm={"lui","auipc"};
vector<string>halting={"fence", "ecall", "ebreak"};

class types {
public:
    string func, rs1, rs2, rd,label_branching;
    pair<string,int> label;
    int imm=0;
    int binRep = -1;
};


string decimalToHex8Digits(int decimalValue) {
    
    stringstream ss;
    ss << uppercase << hex << decimalValue; //convert to Hexadecimal and in uppercase
    string hexString = ss.str();
    
    while (hexString.length() < 8) {
        hexString = "0" + hexString;    // Pad with '0' to achieve 8 digits
    }
    
    hexString = "0x" + hexString; // Add "0x" at the beginning

    return hexString;
}



vector<int> r(32, 0);  // Array for register values, initialized to 0
int programCounter = 0;

map <string,int> register_File;

void initialize() {
    // Initialize named registers with their indices
    register_File["zero"] = 0;  // Constant 0 register
    register_File["ra"] = 1;    // Return address
    register_File["sp"] = 2;    // Stack pointer
    register_File["gp"] = 3;    // Global pointer
    register_File["tp"] = 4;    // Thread pointer
    register_File["t0"] = 5;    // Temporary/alternate link register
    register_File["t1"] = 6;    // Temporaries
    register_File["t2"] = 7;
    register_File["s0"] = 8;    // Saved register/frame pointer
    register_File["fp"] = 8;    // Frame pointer (same as s0)
    register_File["s1"] = 9;    // Saved register

    // Initialize argument registers (a0-a7)
    for (int i = 0; i <= 7; ++i) {
        register_File["a" + to_string(i)] = 10 + i;
    }

    // Initialize additional saved registers (s2-s11)
    for (int i = 2; i <= 11; ++i) {
        register_File["s" + to_string(i)] = 16 + i;
    }

    // Initialize temporary registers (t3-t6)
    for (int i = 0; i <= 3; ++i) {
        register_File["t" + to_string(3 + i)] = 28 + i;
    }

    // Initialize the first element of the r array
    r[0] = 0;
}


map<int, int> memory;
//load instructions into memory
//load program data into memory
bool initializeMemory(map<int, int>& memory, int starting_Address, vector<types>& instructions, vector<pair<int, int>>progData)
{
    
    //fadel a3raf type el program data eh (string, int, char, etc. ) 3ashan el number of bytes it will take up
    for(auto it = progData.begin(); it != progData.end(); it++)
    {
        memory[it->first] = it->second;
    }

    int count = 0;
    for(auto it = instructions.begin(); it != instructions.end(); it ++)
    {
        it->label.second = starting_Address + count;

        for(int i = 0; i < 4; i++)
        {
            memory[starting_Address + count + i] = it->binRep;

            // if(memory.count(starting_Address + count + i) == 0)
            // {
            //     memory[starting_Address + count + i] = it->binRep;
            // } else
            // {
            //     conflict
            // }
        }
        count += 4;
    }



    return true;
}

void Functions(vector<types>& instructions, vector<string> userInput, int startingAdd) {

    bool haltingflag=0;

    for(auto inst  = instructions.begin(); inst != instructions.end() && haltingflag!=1; inst ++) {
        bool branchingFlag = false;
        bool jumpingFlag = false;
        //• Arithmetic: add, addi, sub
        if(inst->func == "add")//1
        {
          
           if(register_File[inst->rd]==0)
           {
               cout << "Executed: " << inst->func << " " << inst->rd  <<","<< inst->rs1 <<"," << inst->rs2 <<" !!!Zero Register cannot be altered!!!"<< endl;
           }
            else
            {

            int valueRS1 =r[register_File[inst->rs1]];
            int valueRS2 =r[register_File[inst->rs2]];
            int result = valueRS1 + valueRS2;
            programCounter = inst->label.second;

            r[register_File[inst->rd]] = result;
            cout << "Executed: " << inst->func << " " << inst->rs1 << "(" << valueRS1 << ") + " << inst->rs2 << "(" << valueRS2 << ") -> " << inst->rd << "(" << result << ")" << endl;
            }
            
            cout << "Memory is unchanged. " << endl;
        }
        else if(inst->func == "sub")//2
        {
            if(register_File[inst->rd]==0)
           {
               cout << "Executed: " << inst->func << " " << inst->rd  <<","<< inst->rs1 <<"," << inst->rs2 <<" !!!Zero Register cannot be altered!!!"<< endl;
           }
            else
            {
            int valueRS1 =r[register_File[inst->rs1]];
            int valueRS2 =r[register_File[inst->rs2]];
            programCounter = inst->label.second;

            int result=0;

            result = valueRS1 - valueRS2;
            r[register_File[inst->rd]] = result;
            cout << "Executed: " << inst->func << " " << inst->rs1 << "(" << valueRS1 << ") - " << inst->rs2 << "(" << valueRS2 << ") -> " << inst->rd << "(" << result << ")" << endl;
            }
            cout << "Memory is unchanged. " << endl;
        }
        else if(inst->func == "addi")//3
        {
             if(register_File[inst->rd]==0)
           {
               cout << "Executed: " << inst->func << " " << inst->rd  <<","<< inst->rs1 <<"," << inst->imm <<" !!!Zero Register cannot be altered!!!"<< endl;
           }
            else
            {
                                
                programCounter = inst->label.second;
              r[register_File[inst->rd]] = r[register_File[inst->rs1]] + inst->imm;
                       cout << "Executed: " << inst->func << " " << inst->rd << "," << inst->rs1 << "," << inst->imm << " Result: " << register_File[inst->rd] << endl;
            }
            cout << "Memory is unchanged. " << endl;

        }
        
        //Load/Store: lw, lh, lhu, lb, lbu, sw, sh, sb, lui
         else if(inst->func == "lw")//4
        {
             if(register_File[inst->rd]==0)
           {
               cout << "Executed: " << inst->func << " " << inst->rd  <<","<< inst->imm <<"(" << inst->rs1 <<") !!!Zero Register cannot be altered!!!"<< endl;
           }
            else
            {
                int add = inst->imm / 4;
                int base = r[register_File[inst->rs1]];
                programCounter = inst->label.second;

                int result = 0;
                for (int i = 0; i < 4; i++)
                {
                    result = result << 8;
                    result |= memory[add + base + i] & 0xFF;
                }
                r[register_File[inst->rd]] = result;

            }
            cout << "Memory is unchanged. " << endl;
        }
        //LOAD sa3at bytla3 255
         else if(inst->func == "lh")//5
        {
             if(register_File[inst->rd]==0)
           {
               cout << "Executed: " << inst->func << " " << inst->rd  <<","<< inst->imm <<"(" << inst->rs1 <<") !!!Zero Register cannot be altered!!!"<< endl;
           }
            else
            {
                int add = inst->imm / 4;
                int base = r[register_File[inst->rs1]];
                programCounter = inst->label.second;

                int result = 0;
                for (int i = 0; i < 2; i++)
                {
                    result = result << 8;
                    result |= memory[add + base + i] & 0xFF;
                }
                
    
                r[register_File[inst->rd]] = result;
            }
            cout << "Memory is unchanged. " << endl;
        }
         else if(inst->func == "lhu")//6
        {
             if(register_File[inst->rd]==0)
           {
               cout << "Executed: " << inst->func << " " << inst->rd  <<","<< inst->imm <<"(" << inst->rs1 <<") !!!Zero Register cannot be altered!!!"<< endl;
           }
            else
            {
                int add = inst->imm / 4;
                int base = r[register_File[inst->rs1]];
                programCounter = inst->label.second;

                unsigned result = 0;
                for (int i = 0; i < 2; i++)
                {
                    result = (unsigned int) result << 8;
                    result |= (unsigned int) memory[add + base + i] & 0xFF;
                }

    
                r[register_File[inst->rd]] = result;
            }
            cout << "Memory is unchanged. " << endl;
        }
         else if(inst->func == "lb")//7
        {
             if(register_File[inst->rd]==0)
           {
               cout << "Executed: " << inst->func << " " << inst->rd  <<","<< inst->imm <<"(" << inst->rs1 <<") !!!Zero Register cannot be altered!!!"<< endl;
           }
            else
            {
                int temp = memory[inst->imm / 4 + r[register_File[inst->rs1]]];
                r[register_File[inst->rd]] = temp;
                programCounter = inst->label.second;
            }
            cout << "Memory is unchanged. " << endl;
        }
        
         else if(inst->func == "lbu")//8
        {
             if(register_File[inst->rd]==0)
           {
               cout << "Executed: " << inst->func << " " << inst->rd  <<","<< inst->imm <<"(" << inst->rs1 <<") !!!Zero Register cannot be altered!!!"<< endl;
           }
            else
            {
                unsigned int temp = memory[inst->imm / 4 + r[register_File[inst->rs1]]];
                r[register_File[inst->rd]] = temp;
                programCounter = inst->label.second;

            }
            cout << "Memory is unchanged. " << endl;
        }
        
        else if(inst->func == "sw")//9
        {
                        
            int number = r[register_File[inst->rs1]];
            
            int off = inst->imm / 4;
            int add = r[register_File[inst->rs2]];

            memory[off + add + 0] = (number >> (24)) & 0xFF;
            memory[off + add + 1] = (number >> (16)) & 0xFF;
            memory[off + add + 2] = (number >> (8)) & 0xFF;
            memory[off + add + 3] = number & 0xFF;

            cout << "Stored the value " << number << " in a word starting at address " << off + add << " in memory. \n";
            programCounter = inst->label.second;

        }
        
            else if(inst->func == "sh")//10
        {
          
            int number = r[register_File[inst->rs1]];
            
            int off = inst->imm / 4;
            int add = r[register_File[inst->rs2]];

            memory[off + add + 0] = (number >> (8)) & 0xFF;
            memory[off + add + 1] = number & 0xFF;
            programCounter = inst->label.second;

            cout << "Stored the value " << number << " in a half-word starting at address " << off + add << " in memory. \n";
        }
        
        else if(inst->func == "sb")//11
        {
            
            memory[inst->imm / 4 + r[register_File[inst->rs2]]] = r[register_File[inst->rs1]];
            programCounter = inst->label.second;

            cout << "Stored the value " << r[register_File[inst->rs1]] << " in a byte starting at address " << inst->imm / 4 + r[register_File[inst->rs2]] << " in memory. \n";
        }
        
         else if(inst->func == "lui")//12
        {
             if(register_File[inst->rd]==0)
           {
               cout << "Executed: " << inst->func << " " << inst->rd  <<","<< inst->imm <<" !!!Zero Register cannot be altered!!!"<< endl;
           }
            else
            {
      int result = inst->imm << 12; // Shift the immediate value left by 12 bits
      r[register_File[inst->rd]] = result;
       programCounter = inst->label.second;

        cout << "Executed: " << inst->func << " " << inst->rd << "," << inst->imm<< "  Now " <<inst->rd<<"("<<result<<")"<<endl;
 
            }
            cout << "Memory is unchanged. " << endl;
        }
       
        //• Logic: sll, slli, srl, srli, sra, srai, and, andi,or, ori, xor, xori
          else  if(inst->func == "sll")//13
        {
          
           if(register_File[inst->rd]==0)
           {
               cout << "Executed: " << inst->func << " " << inst->rd  <<","<< inst->rs1 <<"," << inst->rs2 <<" !!!Zero Register cannot be altered!!!"<< endl;
           }
            else
            {
                  int valueRS1 = r[register_File[inst->rs1]];
                  int valueRS2 = r[register_File[inst->rs2]];
                  int result = valueRS1 << valueRS2;
                  programCounter = inst->label.second;

                  r[register_File[inst->rd]] = result;

                  cout << "Executed: " << inst->func << " " << inst->rs1 << "(" << valueRS1 << ") shift left logical by " << inst->rs2 << "(" << valueRS2 << ") -> " << inst->rd << "(" << result << ")" << endl;
             
            
             }
            cout << "Memory is unchanged. " << endl;
        }
            else if(inst->func == "slli")//14
        {
          
           if(register_File[inst->rd]==0)
           {
               cout << "Executed: " << inst->func << " " << inst->rd  <<","<< inst->rs1 <<"," << inst->imm <<" !!!Zero Register cannot be altered!!!"<< endl;
           }
            else
            {
                  int valueRS1 = r[register_File[inst->rs1]];
                  int valueRS2 = inst->imm;
                  int result = valueRS1 << valueRS2;
                  programCounter = inst->label.second;
                  r[register_File[inst->rd]] = result;

                  cout << "Executed: " << inst->func << " " << inst->rs1 << "(" << valueRS1 << ") shift left logical by " << "(" << valueRS2 << ") -> " << inst->rd << "(" << result << ")" << endl;
             
         
             }
            cout << "Memory is unchanged. " << endl;
        }
        
            else if(inst->func == "srl")//15
        {
          
           if(register_File[inst->rd]==0)
           {
               cout << "Executed: " << inst->func << " " << inst->rd  <<","<< inst->rs1 <<"," << inst->rs2 <<" !!!Zero Register cannot be altered!!!"<< endl;
           }
            else
            {
                  unsigned int valueRS1 = static_cast<unsigned int>( r[register_File[inst->rs1]] );
                  int valueRS2 = r[register_File[inst->rs2]];
                  int result = valueRS1 >> valueRS2;
                  programCounter = inst->label.second;
                  r[register_File[inst->rd]] = result;

 cout << "Executed: " << inst->func << " " << inst->rs1 << "(" << valueRS1 << ") shift right logical by " << inst->rs2 << "(" << valueRS2 << ") -> " << inst->rd << "(" << result << ")" << endl;
            
             }
            cout << "Memory is unchanged. " << endl;
        }
               else if(inst->func == "srli")//16
        {
          
           if(register_File[inst->rd]==0)
           {
               cout << "Executed: " << inst->func << " " << inst->rd  <<","<< inst->rs1 <<"," << inst->imm <<" !!!Zero Register cannot be altered!!!"<< endl;
           }
            else
            {
                unsigned int valueRS1 = static_cast<unsigned int> (r[register_File[inst->rs1]]);
                  int valueRS2 = inst->imm;
                  int result = valueRS1 >> valueRS2;
                  programCounter = inst->label.second;

                  r[register_File[inst->rd]] = result;

                   cout << "Executed: " << inst->func << " " << inst->rs1 << "(" << valueRS1 << ") shift right logical by " << "(" << valueRS2 << ") -> " << inst->rd << "(" << result << ")" << endl;
             
             }
            cout << "Memory is unchanged. " << endl;
        }
        
               else if(inst->func == "sra")//17
        {
          
           if(register_File[inst->rd]==0)
           {
               cout << "Executed: " << inst->func << " " << inst->rd  <<","<< inst->rs1 <<"," << inst->rs2 <<" !!!Zero Register cannot be altered!!!"<< endl;
           }
            else
            {
                 int valueRS1 = r[register_File[inst->rs1]];
                 int valueRS2 = r[register_File[inst->rs2]];
                 int result = valueRS1 >> valueRS2;
                 programCounter = inst->label.second;

                  r[register_File[inst->rd]] = result;

                  cout << "Executed: " << inst->func << " " << inst->rs1 << "(" << valueRS1 << ") shift right arithmetic by " << inst->rs2 << "(" << valueRS2 << ") -> " << inst->rd << "(" << result << ")" << endl;
             
            
             }
            cout << "Memory is unchanged. " << endl;
        }
        
               else if(inst->func == "srai")//18
        {
          
           if(register_File[inst->rd]==0)
           {
                cout << "Executed: " << inst->func << " " << inst->rd  <<","<< inst->rs1 <<"," << inst->imm <<" !!!Zero Register cannot be altered!!!"<< endl;
           }
            else
            {
                  int valueRS1 = r[register_File[inst->rs1]];
                  int valueRS2 = inst->imm;
                  int result = valueRS1 >> valueRS2;
                  programCounter = inst->label.second;

                  r[register_File[inst->rd]] = result;

                  cout << "Executed: " << inst->func << " " << inst->rs1 << "(" << valueRS1 << ") shift right arithmetic by " << "(" << valueRS2 << ") -> " << inst->rd << "(" << result << ")" << endl;
             
         
             }
            cout << "Memory is unchanged. " << endl;
        }
        
               else if(inst->func == "and")//19
        {
          
           if(register_File[inst->rd]==0)
           {
               cout << "Executed: " << inst->func << " " << inst->rd  <<","<< inst->rs1 <<"," << inst->rs2 <<" !!!Zero Register cannot be altered!!!"<< endl;
           }
            else
            {
                int valueRS1 = r[register_File[inst->rs1]];
                int valueRS2 = r[register_File[inst->rs2]];
                int result = valueRS1 & valueRS2; // Bitwise AND operation
                programCounter = inst->label.second; 
                r[register_File[inst->rd]] = result;

                cout << "Executed: " << inst->func << " " << inst->rs1 << "(" << valueRS1 << ") & " << inst->rs2 << "(" << valueRS2 << ") -> " << inst->rd << "(" << result << ")" << endl;
             
             }
            cout << "Memory is unchanged. " << endl;
        }
        
               else if(inst->func == "andi")//20
        {
          
           if(register_File[inst->rd]==0)
           {
               cout << "Executed: " << inst->func << " " << inst->rd  <<","<< inst->rs1 <<"," << inst->imm <<" !!!Zero Register cannot be altered!!!"<< endl;
           }
            else
            {
                //func code
                programCounter = inst->label.second; 
                cout << "Memory is unchanged. " << endl;
             }
            
        }
        
                else if(inst->func == "or")//21
        {
          
           if(register_File[inst->rd]==0)
           {
               cout << "Executed: " << inst->func << " " << inst->rd  <<","<< inst->rs1 <<"," << inst->rs2 <<" !!!Zero Register cannot be altered!!!"<< endl;
           }
            else
            {
                int valueRS1 = r[register_File[inst->rs1]];
                int valueRS2 = r[register_File[inst->rs2]];
                int result = valueRS1 | valueRS2;
                programCounter = inst->label.second;
                r[register_File[inst->rd]] = result;

                cout << "Executed: " << inst->func << " " << inst->rs1 << "(" << valueRS1 << ") & " << inst->rs2 << "(" << valueRS2 << ") -> " << inst->rd << "(" << result << ")" << endl;
            
             }
            cout << "Memory is unchanged. " << endl;
        }
        
              else if(inst->func == "ori")//22
        {
          
           if(register_File[inst->rd]==0)
           {
                cout << "Executed: " << inst->func << " " << inst->rd  <<","<< inst->rs1 <<"," << inst->imm <<" !!!Zero Register cannot be altered!!!"<< endl;
           }
            else
            {
                int valueRS1 = r[register_File[inst->rs1]];
                int valueRS2 = inst->imm;
                int result = valueRS1 | valueRS2;
                programCounter = inst->label.second;
                result=r[register_File[inst->rd]];

                cout << "Executed: " << inst->func << " " << inst->rs1 << "(" << valueRS1 << ") & " << inst->rs2 << "(" << valueRS2 << ") -> " << inst->rd << "(" << result << ")" << endl;
            }
             cout << "Memory is unchanged. " << endl;
            
        }
        
              else if(inst->func == "xor")//23
        {
          
           if(register_File[inst->rd]==0)
           {
               cout << "Executed: " << inst->func << " " << inst->rd  <<","<< inst->rs1 <<"," << inst->rs2 <<" !!!Zero Register cannot be altered!!!"<< endl;
           }
            else
            {
                int valueRS1 = r[register_File[inst->rs1]];
                int valueRS2 = r[register_File[inst->rs2]];
                int result = valueRS1 ^ valueRS2;
                programCounter = inst->label.second;
                 r[register_File[inst->rd]] = result;

                 cout << "Executed: " << inst->func << " " << inst->rs1 << "(" << valueRS1 << ") & " << inst->rs2 << "(" << valueRS2 << ") -> " << inst->rd << "(" << result << ")" << endl;
             
             }
            cout << "Memory is unchanged. " << endl;
        }
        
        else if(inst->func == "xori")//24
        {
          
           if(register_File[inst->rd]==0)
           {
               cout << "Executed: " << inst->func << " " << inst->rd  <<","<< inst->rs1 <<"," << inst->imm <<" !!!Zero Register cannot be altered!!!"<< endl;
           }
            else
            {
                int valueRS1 = r[register_File[inst->rs1]];
                     int valueRS2 = inst->imm;
                     int result = valueRS1 ^ valueRS2;
                programCounter = inst->label.second;

                     r[register_File[inst->rd]] =result;

                     cout << "Executed: " << inst->func << " " << inst->rs1 << "(" << valueRS1 << ") & " << inst->rs2 << "(" << valueRS2 << ") -> " << inst->rd << "(" << result << ")" << endl;
             }
            cout << "Memory is unchanged. " << endl;
        }
        
        //• Control flow: beq, bne, blt, bltu, bge, bgeu, jal,jalr
        else if(inst->func == "beq")//25
        {
    
            if(r[register_File[inst->rs1]] == r[register_File[inst->rs2]])
            {
                for(auto it = instructions.begin(); it != instructions.end(); it ++)
                {
                    if(it->label.first == inst->label_branching)
                    {
                        inst = it;
                        inst --;
                        programCounter = it->label.second;
                        branchingFlag = true;
                        break;
                    }
                }
            }
            cout << "Memory is unchanged. " << endl;
        }
        
         else if(inst->func == "bne")//26
        {
    
            if(r[register_File[inst->rs1]] != r[register_File[inst->rs2]])
            {
                for(auto it = instructions.begin(); it != instructions.end(); it ++)
                {
                    if(it->label.first == inst->label_branching)
                    {
                        inst = it;
                        inst --;
                        programCounter = it->label.second;
                        branchingFlag = true;
                        break;
                    }
                }
            }
            cout << "Memory is unchanged. " << endl;
        }
        
         else if(inst->func == "blt")//27
        {
    
            if(r[register_File[inst->rs1]] < r[register_File[inst->rs2]])
            {
                for(auto it = instructions.begin(); it != instructions.end(); it ++)
                {
                    if(it->label.first == inst->label_branching)
                    {
                        inst = it;
                        inst --;
                        programCounter = it->label.second;
                        branchingFlag = true;
                        break;
                    }
                }
            }
            cout << "Memory is unchanged. " << endl;
        }
        
         else if(inst->func == "bltu")//28
        {
    
            if((unsigned int)r[register_File[inst->rs1]] == (unsigned int)r[register_File[inst->rs2]])
            {
                for(auto it = instructions.begin(); it != instructions.end(); it ++)
                {
                    if(it->label.first == inst->label_branching)
                    {
                        inst = it;
                        inst --;
                        programCounter = it->label.second;
                        branchingFlag = true;
                        break;
                    }
                }
            }
            cout << "Memory is unchanged. " << endl;
        }
        
         else if(inst->func == "bge")//29
        {
    
            if(r[register_File[inst->rs1]] > r[register_File[inst->rs2]])
            {
                for(auto it = instructions.begin(); it != instructions.end(); it ++)
                {
                    if(it->label.first == inst->label_branching)
                    {
                        inst = it;
                        inst --;
                        programCounter = it->label.second;
                        branchingFlag = true;
                        break;
                    }
                }
            }
            cout << "Memory is unchanged. " << endl;
        }
        
         else if(inst->func == "bgeu")//30
        {
    
            if((unsigned int)r[register_File[inst->rs1]] > (unsigned int)r[register_File[inst->rs2]])
            {
                for(auto it = instructions.begin(); it != instructions.end(); it ++)
                {
                    if(it->label.first == inst->label_branching)
                    {
                        inst = it;
                        inst --;
                        programCounter = it->label.second;
                        branchingFlag = true;
                        break;
                    }
                }
            }
            cout << "Memory is unchanged. " << endl;
        }
        
         else if(inst->func == "jal")//31
        {
            if(inst == instructions.end() - 1)
                r[register_File[inst->rd]] = instructions.begin()->label.second;
            else
                r[register_File[inst->rd]] = ((inst + 1)->label.second);

            for(auto it = instructions.begin(); it != instructions.end(); it ++)
            {
                if(it->label.first == inst->label_branching)
                {
                    inst = it;
                    inst --;
                    programCounter = it->label.second;
                    jumpingFlag = true;
                    break;
                }
            }

            cout << "Memory is unchanged. " << endl;
        }
        
         else if(inst->func == "jalr")//32
        {
            if(inst == instructions.end() - 1)
                r[register_File[inst->rd]] = instructions.begin()->label.second;
            else
                r[register_File[inst->rd]] = ((inst + 1)->label.second);

            int targetAddress = r[register_File[inst->rs1]] + inst->imm;
                
            for(auto it = instructions.begin(); it != instructions.end(); it ++)
            {
                if(it->label.second == targetAddress)
                {
                    inst = it;
                    inst --;
                    programCounter = it->label.second;
                    jumpingFlag = true;
                    break;
                }
            }

                //func code
            cout << "Memory is unchanged. " << endl;
        }
        
        //Comparison: slt, slti, sltu, sltui
                else if(inst->func == "slt")//33
        {
          
           if(register_File[inst->rd]==0)
           {
               cout << "Executed: " << inst->func << " " << inst->rd  <<","<< inst->rs1 <<"," << inst->rs2 <<" !!!Zero Register cannot be altered!!!"<< endl;
           }
            else
            {
                 int valueRS1 = r[register_File[inst->rs1]];
                 int valueRS2 = r[register_File[inst->rs2]];
                 if(valueRS1<valueRS2)
                 {
                     r[register_File[inst->rd]] = 1;
                 }
                 else
                 {
                     r[register_File[inst->rd]] = 0;
                 }
                 programCounter = inst->label.second;
                 int result=r[register_File[inst->rd]];
                 cout << "Executed: " << inst->func << " " << inst->rs1 << "(" << valueRS1 << ") & " << inst->rs2 << "(" << valueRS2 << ") -> " << inst->rd << "(" << result << ")" << endl;
             
             }
            cout << "Memory is unchanged. " << endl;
        }
        
                else if(inst->func == "slti")//34
        {
          
           if(register_File[inst->rd]==0)
           {
              cout << "Executed: " << inst->func << " " << inst->rd  <<","<< inst->rs1 <<"," << inst->imm <<" !!!Zero Register cannot be altered!!!"<< endl;
           }
            else
            {
                  int valueRS1 = r[register_File[inst->rs1]];
                 int valueRS2 = inst->imm;
                 if(valueRS1<valueRS2)
                 {
                     r[register_File[inst->rd]] = 1;
                 }
                 else
                 {
                     r[register_File[inst->rd]] = 0;
                 }
                 programCounter = inst->label.second;
                 int result=r[register_File[inst->rd]];
                 cout << "Executed: " << inst->func << " " << inst->rs1 << "(" << valueRS1 << ") & " << inst->rs2 << "(" << valueRS2 << ") -> " << inst->rd << "(" << result << ")" << endl;
          
             }
            cout << "Memory is unchanged. " << endl;
        }
        
                else if(inst->func == "sltu")//35
        {
          
           if(register_File[inst->rd]==0)
           {
               cout << "Executed: " << inst->func << " " << inst->rd  <<","<< inst->rs1 <<"," << inst->rs2 <<" !!!Zero Register cannot be altered!!!"<< endl;
           }
            else
            {
                   unsigned int valueRS1 = static_cast<unsigned int>(r[register_File[inst->rs1]]);
                            unsigned int valueRS2 = static_cast<unsigned int>(r[register_File[inst->rs2]]);

                            
                            if(valueRS1 < valueRS2)
                            {
                                r[register_File[inst->rd]] = 1;
                            }
                            else
                            {
                                r[register_File[inst->rd]] = 0;
                            }
                             int result=r[register_File[inst->rd]];
                programCounter = inst->label.second;

                cout << "Executed: " << inst->func << " " << inst->rs1 << "(" << valueRS1 << ") & " << inst->rs2 << "(" << valueRS2 << ") -> " << inst->rd << "(" << result << ")" << endl;

              
             }
            cout << "Memory is unchanged. " << endl;
        }
        
                  else if(inst->func == "sltiu")//36
        {
          
           if(register_File[inst->rd]==0)
           {
              cout << "Executed: " << inst->func << " " << inst->rd  <<","<< inst->rs1 <<"," << inst->imm <<" !!!Zero Register cannot be altered!!!"<< endl;
           }
            else
            {
                unsigned int valueRS1 = static_cast<unsigned int>(r[register_File[inst->rs1]]);
                 unsigned int valueRS2 = static_cast<unsigned int>(inst->imm);

                 
                 if(valueRS1 < valueRS2)
                 {
                     r[register_File[inst->rd]] = 1;
                 }
                 else
                 {
                     r[register_File[inst->rd]] = 0;
                 }
                  int result=r[register_File[inst->rd]];
                programCounter = inst->label.second;

               cout << "Executed: " << inst->func << " " << inst->rs1 << "(" << valueRS1 << ") & " << inst->rs2 << "(" << valueRS2 << ") -> " << inst->rd << "(" << result << ")" << endl;

            
             }
            cout << "Memory is unchanged. " << endl;
        }
        
        else if(inst->func == "auipc")//37
        {
          
           if(register_File[inst->rd]==0)
           {
                cout << "Executed: " << inst->func << " " << inst->rd  <<","<< inst->imm <<" !!!Zero Register cannot be altered!!!"<< endl;
           }
            else
            {
        int result = programCounter + (inst->imm << 12);
        r[register_File[inst->rd]] = result;
        programCounter = inst->label.second;
        cout << "Executed: " << inst->func << " " << inst->rd << ","<< inst->imm<<". -> (" << programCounter << ") + " << inst->imm << " -> " << inst->rd << "(" << result << ")" << endl;
             }
            cout << "Memory is unchanged. " << endl;
        }
        
          else if(inst->func == "fence")//38
        {
    
             haltingflag=1;
             cout << "Executed: " << inst->func << " Program execution finsihed due to 'halt' instruction." << endl;

            
        }
        
         
          else if(inst->func == "ecall")//39
        {
    
             haltingflag=1;
            cout << "Executed: " << inst->func << " Program execution finsihed due to 'halt' instruction." << endl;
            
        }
        
         
          else if(inst->func == "ebreak")//40
        {
    
             haltingflag=1;
             cout << "Executed: " << inst->func << " Program execution finsihed due to 'halt' instruction." << endl;
            
        }
        
        // Output the current state of the registers

         if(jumpingFlag)
        {
            cout << "Jumping now to label: " << (inst + 1)->label.first << endl;
            cout << "Current Program Counter Value:  " << programCounter << endl;
            cout << "---------------------------" << endl;
            cout << "Register File State after executing jumping instruction: " << endl;
            cout<<"           Decimal                  Binary                         Hexadecimal "<<endl;
            for (const auto& reg : register_File) {
                cout << reg.first << " (r[" << reg.second << "]): " << r[reg.second]<<"          0b" << bitset<32>(r[reg.second]) << "          " <<decimalToHex8Digits(r[reg.second])<<endl;
            }          
            cout << "---------------------------" << endl;
  
            continue;
        }

        if(branchingFlag)
        {
            cout << "Branching now to label: " << (inst + 1)->label.first << endl;
            cout << "Current Program Counter Value:  " << programCounter << endl;
            cout << "---------------------------" << endl;
            continue;
        }
        cout << "Register File State after executing instruction: " << userInput[(programCounter - startingAdd) / 4] << endl;
        cout<<"           Decimal                  Binary                         Hexadecimal "<<endl;
        for (const auto& reg : register_File) {
            cout << reg.first << " (r[" << reg.second << "]): " << r[reg.second]<<"          0b" << bitset<32>(r[reg.second]) << "          " <<decimalToHex8Digits(r[reg.second])<<endl;
        }

        cout << "Current Program Counter Value:  " << programCounter << endl;
        cout << "---------------------------" << endl;
    }

}

vector<types> read(vector<string> x) {
    vector<types> result;
    int index=0; //index of each instruction in the pro
    for (auto& str : x) {
        stringstream ss(str);
        string first_word, rd, rs1, rs2, imm, label_bran, shamt,jumping_label;
        types t;
        t.label.second=index;
        // Extract first word from the string
        ss >> first_word;

        // Check if there is a label or not
        if (first_word.back() == ':') {
            t.label.first= first_word.substr(0, first_word.size() - 1);//add label
            ss >> t.func;
        } else {
            t.func = first_word; // No label, only fuction
        }
        // Check if the function is R-type
        if (find(R_type.begin(), R_type.end(), t.func) != R_type.end()) {
            getline(ss, rd, ',');
            getline(ss, rs1, ',');
            ss >> rs2;

            // Assign the source and destination
            t.rd = rd.substr(rd.find(' ') + 1);
            t.rs1 = rs1.substr(rs1.find(' ') + 1);
            t.rs2 = rs2;

            result.push_back(t);
            // func rd,rs1,rs2
        }
        // Check if the function is I-type
        else if(find(I_type.begin(),I_type.end(),t.func) != I_type.end()) {
            getline(ss, rd, ',');
            getline(ss, rs1, ',');
            ss >> imm;

            // Assign the destination, source, and immediate
            t.rd = rd.substr(rd.find(' ') + 1);
            t.rs1 = rs1.substr(rs1.find(')')+1 );
            t.imm = stoi(imm);

            result.push_back(t);
            // func rd,rs1,imm
        }
        else if(find(I_type2.begin(),I_type2.end(),t.func)!=I_type2.end())
        {
           getline(ss, rd, ',');
           getline(ss, imm, '('); //imm won't include any paranthesis
           ss >> rs1;//rs1 will include the closing paranthesis
           ss.ignore();

    
          t.rd = rd.substr(rd.find(' ') + 1);
          t.imm = stoi(imm);
          t.rs1 = rs1.substr(0, rs1.find(')'));

          result.push_back(t);
           // func rd,imm(rs1)
        }
        else if(find(B_type.begin(),B_type.end(),t.func)!=B_type.end())
        {
            getline(ss,rs1,',');
            getline(ss,rs2,',');
            ss>>label_bran;
            t.rs1=rs1.substr(rs1.find(' ')+1);
            t.rs2=rs2.substr(rs2.find(' ')+1);
            t.label_branching=label_bran;
            result.push_back(t);
            // func rs1,rs2,label
        }
        else if(find(S_type.begin(),S_type.end(),t.func)!=S_type.end())
        {
           getline(ss, rs1, ',');
           getline(ss, imm, '('); //imm won't include any paranthesis
           ss >> rs2;//rs1 will include the closing paranthesis
           ss.ignore();

    
          t.rs1 = rs1.substr(rs1.find(' ') + 1);
          t.imm = stoi(imm);
          t.rs2 = rs2.substr(0, rs2.find(')'));

          result.push_back(t);
          //func rs1,imm(rs2)
        }
        else if(find(jump_link.begin(), jump_link.end(),t.func)!=jump_link.end())
        {
           getline(ss, rd, ',');
           getline(ss, imm, '('); //imm won't include any paranthesis
           ss >> rs1;//rs1 will include the closing paranthesis
           ss.ignore();

    
          t.rd = rd.substr(rd.find(' ') + 1);
          t.imm = stoi(imm);
          t.rs1 = rs1.substr(0, rs1.find(')'));
          result.push_back(t);
          //func rd,imm(rs1)
        }
        else if(find(jump2.begin(), jump2.end(),t.func)!=jump2.end())
        {
            getline(ss,rd,',');
            ss>>jumping_label;
            t.rd = rd.substr(rd.find(' ') + 1);
            t.label_branching=jumping_label;
            result.push_back(t);
            //func rd,label
            
        }
        else if(find(shifiting.begin(),shifiting.end(),t.func) != shifiting.end()) {
            getline(ss, rd, ',');
            getline(ss, rs1, ',');
            ss >> shamt;

            // Assign the destination, source, and immediate
            t.rd = rd.substr(rd.find(' ') + 1);
            t.rs1 = rs1.substr(rs1.find(')')+1 );
            t.imm = stoi(shamt);

            result.push_back(t);
             //func rd,rs1,imm
        }
        else if(find(lower_upperImm.begin(), lower_upperImm.end(),t.func)!=lower_upperImm.end())
        {
            getline(ss,rd,',');
            ss>>imm;
            t.rd = rd.substr(rd.find(' ') + 1);
            t.imm=stoi(imm);
            result.push_back(t);
            //  func rd,imm
            
        }
         else if(find(halting.begin(), halting.end(),t.func)!=lower_upperImm.end())
        {
        
          result.push_back(t);
            //func
        }
        index++;
    }

    return result;
}


int main() {
    
    vector<string> instructions;
    string input;

    cout << "Enter any data to be initially loaded into the memory (type 'finish' to exist the loop):" << endl;
    string add, val;
    vector<pair<int, int>> progData;
    pair<int, int> temp;

    while (true) {
        cout << "Starting address of data item (please enter addresses in order):  ";
        cin >> add;
        if (add == "finish") {
            break;
        }

        cout << "Value of data item:  ";
        cin >> val;
        temp.first = stoi(add);
        temp.second = stoi(val);
        progData.push_back(temp);
    }

    cout << "Enter instructions (type 'finish' to exist the loop):" << endl;

    // taking input until the user enters 'finish'
    while (true) {
        getline(cin, input);
        if (input == "finish") {
            break;
        }
        instructions.push_back(input);
    }
    initialize();

    instructions.erase(instructions.begin());
    vector<types> res = read(instructions);
   
    // // Output the result for demonstration
    // for (const auto& t : res) {
    //     cout << "label: " << t.label.first << " , func: " << t.func << ", rd: " << t.rd
    //          << ", rs1: " << t.rs1 << ", rs2: " << t.rs2 << ", imm: " << t.imm
    //          << ", branching_label: " << t.label_branching << endl;
    // }


    bool repeat = false;
    int progSize = res.size() * 4;
    int startingAdd;
    do
    {
        cout << "Enter the starting address of the program: " << endl;
        cin >> startingAdd;
        repeat = false;

        for(int i = 0; i < progData.size(); i ++)
        {

            if((progData[i + 1].first - progData[i].first) < progSize && startingAdd > progData[i].first && startingAdd < progData[i + 1].first && (i + 1) != progData.size())
            {
                cout << "Please enter a non-conflicting starting address. " << endl;
                repeat = true;
            }

            if(((startingAdd < progData[0].first) && (startingAdd + progSize > progData[0].first)) || progData[i].first == startingAdd)
            {
                cout << "Please enter a non-conflicting starting address. " << endl;
                repeat = true;
            }

        }

    } while (repeat);
    
    programCounter = startingAdd;
    initializeMemory(memory, startingAdd, res, progData);
    Functions(res, instructions, startingAdd);


    return 0;
}

