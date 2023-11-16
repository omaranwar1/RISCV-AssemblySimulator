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
     
};
vector<int> r(32, 0);  // Array for register values, initialized to 0
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
void Functions(vector<types> instructions) {
    
    for(auto& inst : instructions) {
        //• Arithmetic: add, addi, sub
        if(inst.func == "add")//1
        {
          
           if(register_File[inst.rd]==0)
           {
               cout << "Executed: " << inst.func << " " << inst.rd  <<","<< inst.rs1 <<"," << inst.rs2 <<" !!!Zero Register cannot be altered!!!"<< endl;
           }
            else 
            {
            int valueRS1 =r[register_File[inst.rs1]];
            int valueRS2 =r[register_File[inst.rs2]];
            int result = valueRS1 + valueRS2;
            
            r[register_File[inst.rd]] = result;
            
            cout << "Executed: " << inst.func << " " << inst.rs1 << "(" << valueRS1 << ") + " << inst.rs2 << "(" << valueRS2 << ") -> " << inst.rd << "(" << result << ")" << endl;
            }
            
        }
        else if(inst.func == "sub")//2
        {
            if(register_File[inst.rd]==0)
           {
               cout << "Executed: " << inst.func << " " << inst.rd  <<","<< inst.rs1 <<"," << inst.rs2 <<" !!!Zero Register cannot be altered!!!"<< endl;
           }
            else 
            {
            int valueRS1 =r[register_File[inst.rs1]];
            int valueRS2 =r[register_File[inst.rs2]];
            
            int result=0;

            result = valueRS1 - valueRS2;
            r[register_File[inst.rd]] = result;
            cout << "Executed: " << inst.func << " " << inst.rs1 << "(" << valueRS1 << ") - " << inst.rs2 << "(" << valueRS2 << ") -> " << inst.rd << "(" << result << ")" << endl;
            }
          
        }   
        else if(inst.func == "addi")//3
        {
            if(register_File[inst.rd]==0)
          {
              cout << "Executed: " << inst.func << " " << inst.rd  <<","<< inst.rs1 <<"," << inst.imm <<" !!!Zero Register cannot be altered!!!"<< endl;
          }
           else
           {
               r[register_File[inst.rd]] = r[register_File[inst.rs1]] + inst.imm;
                       cout << "Executed: " << inst.func << " " << inst.rd << "," << inst.rs1 << "," << inst.imm << " Result: " << register_File[inst.rd] << endl;
           }
            
        }
        
        //Load/Store: lw, lh, lhu, lb, lbu, sw, sh, sb, lui
         else if(inst.func == "lw")//4
        {
             if(register_File[inst.rd]==0)
           {
               cout << "Executed: " << inst.func << " " << inst.rd  <<","<< inst.imm <<"(" << inst.rs1 <<") !!!Zero Register cannot be altered!!!"<< endl;
           }
            else 
            {
          //func code
            }
            
        }
         else if(inst.func == "lh")//5
        {
             if(register_File[inst.rd]==0)
           {
               cout << "Executed: " << inst.func << " " << inst.rd  <<","<< inst.imm <<"(" << inst.rs1 <<") !!!Zero Register cannot be altered!!!"<< endl;
           }
            else 
            {
          //func code
            }
            
        }
         else if(inst.func == "lhu")//6
        {
             if(register_File[inst.rd]==0)
           {
               cout << "Executed: " << inst.func << " " << inst.rd  <<","<< inst.imm <<"(" << inst.rs1 <<") !!!Zero Register cannot be altered!!!"<< endl;
           }
            else 
            {
          //func code
            }
            
        }
         else if(inst.func == "lb")//7
        {
             if(register_File[inst.rd]==0)
           {
               cout << "Executed: " << inst.func << " " << inst.rd  <<","<< inst.imm <<"(" << inst.rs1 <<") !!!Zero Register cannot be altered!!!"<< endl;
           }
            else 
            {
          //func code
            }
            
        }
        
         else if(inst.func == "lbu")//8
        {
             if(register_File[inst.rd]==0)
           {
               cout << "Executed: " << inst.func << " " << inst.rd  <<","<< inst.imm <<"(" << inst.rs1 <<") !!!Zero Register cannot be altered!!!"<< endl;
           }
            else 
            {
          //func code
            }
            
        }
        
            else if(inst.func == "sw")//9
        {
             
          //func code

            
        }
        
            else if(inst.func == "sh")//10
        {
          
          //func code
            
        }
        
            else if(inst.func == "sb")//11
        {
            
          //func code
            
        }
        
         else if(inst.func == "lui")//12
        {
             if(register_File[inst.rd]==0)
           {
               cout << "Executed: " << inst.func << " " << inst.rd  <<","<< inst.imm <<" !!!Zero Register cannot be altered!!!"<< endl;
           }
            else 
            {
          //func code
            }
            
        }
       
        //• Logic: sll, slli, srl, srli, sra, srai, and, andi,or, ori, xor, xori
          else  if(inst.func == "sll")//13
        {
          
           if(register_File[inst.rd]==0)
           {
               cout << "Executed: " << inst.func << " " << inst.rd  <<","<< inst.rs1 <<"," << inst.rs2 <<" !!!Zero Register cannot be altered!!!"<< endl;
           }
            else 
            {
                //func code
             }
            
        }
            else if(inst.func == "slli")//14
        {
          
           if(register_File[inst.rd]==0)
           {
               cout << "Executed: " << inst.func << " " << inst.rd  <<","<< inst.rs1 <<"," << inst.imm <<" !!!Zero Register cannot be altered!!!"<< endl;
           }
            else 
            {
                //func code
             }
            
        }
        
            else if(inst.func == "srl")//15
        {
          
           if(register_File[inst.rd]==0)
           {
               cout << "Executed: " << inst.func << " " << inst.rd  <<","<< inst.rs1 <<"," << inst.rs2 <<" !!!Zero Register cannot be altered!!!"<< endl;
           }
            else 
            {
                //func code
             }
            
        }
               else if(inst.func == "srli")//16
        {
          
           if(register_File[inst.rd]==0)
           {
               cout << "Executed: " << inst.func << " " << inst.rd  <<","<< inst.rs1 <<"," << inst.imm <<" !!!Zero Register cannot be altered!!!"<< endl;
           }
            else 
            {
                //func code
             }
            
        }
        
               else if(inst.func == "sra")//17
        {
          
           if(register_File[inst.rd]==0)
           {
               cout << "Executed: " << inst.func << " " << inst.rd  <<","<< inst.rs1 <<"," << inst.rs2 <<" !!!Zero Register cannot be altered!!!"<< endl;
           }
            else 
            {
                //func code
             }
            
        }
        
               else if(inst.func == "srai")//18
        {
          
           if(register_File[inst.rd]==0)
           {
                cout << "Executed: " << inst.func << " " << inst.rd  <<","<< inst.rs1 <<"," << inst.imm <<" !!!Zero Register cannot be altered!!!"<< endl;
           }
            else 
            {
                //func code
             }
            
        }
        
               else if(inst.func == "and")//19
        {
          
           if(register_File[inst.rd]==0)
           {
               cout << "Executed: " << inst.func << " " << inst.rd  <<","<< inst.rs1 <<"," << inst.rs2 <<" !!!Zero Register cannot be altered!!!"<< endl;
           }
            else 
            {
                //func code
             }
            
        }
        
               else if(inst.func == "andi")//20
        {
          
            if(register_File[inst.rd]==0)
            {
                cout << "Executed: " << inst.func << " " << inst.rd  <<","<< inst.rs1 <<"," << inst.rs2 <<" !!!Zero Register cannot be altered!!!"<< endl;
            }
             else
             {
                 int valueRS1 = r[register_File[inst.rs1]];
                         int valueRS2 = r[register_File[inst.rs2]];
                         int result = valueRS1 & valueRS2; // Bitwise AND operation

                         r[register_File[inst.rd]] = result;

                         cout << "Executed: " << inst.func << " " << inst.rs1 << "(" << valueRS1 << ") & " << inst.rs2 << "(" << valueRS2 << ") -> " << inst.rd << "(" << result << ")" << endl;
              }
            
        }
        
                else if(inst.func == "or")//21
        {
          
            if(register_File[inst.rd]==0)
            {
                cout << "Executed: " << inst.func << " " << inst.rd  <<","<< inst.rs1 <<"," << inst.rs2 <<" !!!Zero Register cannot be altered!!!"<< endl;
            }
             else
             {
                         int valueRS1 = r[register_File[inst.rs1]];
                         int valueRS2 = r[register_File[inst.rs2]];
                         int result = valueRS1 | valueRS2;

                         r[register_File[inst.rd]] = result;

                         cout << "Executed: " << inst.func << " " << inst.rs1 << "(" << valueRS1 << ") & " << inst.rs2 << "(" << valueRS2 << ") -> " << inst.rd << "(" << result << ")" << endl;
              }
            
        }
        
              else if(inst.func == "ori")//22
        {
          
           if(register_File[inst.rd]==0)
           {
                cout << "Executed: " << inst.func << " " << inst.rd  <<","<< inst.rs1 <<"," << inst.imm <<" !!!Zero Register cannot be altered!!!"<< endl;
           }
            else 
            {
                //func code
             }
            
        }
        
              else if(inst.func == "xor")//23
        {
          
            if(register_File[inst.rd]==0)
            {
                cout << "Executed: " << inst.func << " " << inst.rd  <<","<< inst.rs1 <<"," << inst.rs2 <<" !!!Zero Register cannot be altered!!!"<< endl;
            }
             else
             {
                 int valueRS1 = r[register_File[inst.rs1]];
                 int valueRS2 = r[register_File[inst.rs2]];
                 int result = valueRS1 ^ valueRS2;

                 r[register_File[inst.rd]] = result;

                 cout << "Executed: " << inst.func << " " << inst.rs1 << "(" << valueRS1 << ") & " << inst.rs2 << "(" << valueRS2 << ") -> " << inst.rd << "(" << result << ")" << endl;
              }
            
        }
        
        else if(inst.func == "xori")//24
        {
          
           if(register_File[inst.rd]==0)
           {
               cout << "Executed: " << inst.func << " " << inst.rd  <<","<< inst.rs1 <<"," << inst.imm <<" !!!Zero Register cannot be altered!!!"<< endl;
           }
            else 
            {
                //func code
             }
            
        }
        
        //• Control flow: beq, bne, blt, bltu, bge, bgeu, jal,jalr
        else if(inst.func == "beq")//25
        {
    
                //func code
            
        }
        
         else if(inst.func == "bne")//26
        {
    
                //func code
            
        }
        
         else if(inst.func == "blt")//27
        {
    
                //func code
            
        }
        
         else if(inst.func == "bltu")//28
        {
    
                //func code
            
        }
        
         else if(inst.func == "bge")//29
        {
    
                //func code
            
        }
        
         else if(inst.func == "bgeu")//30
        {
    
                //func code
            
        }
        
         else if(inst.func == "jal")//31
        {
    
                //func code
            
        }
        
         else if(inst.func == "jalr")//32
        {
    
                //func code
            
        }
        
        //Comparison: slt, slti, sltu, sltui
                else if(inst.func == "slt")//33
        {
          
           if(register_File[inst.rd]==0)
           {
               cout << "Executed: " << inst.func << " " << inst.rd  <<","<< inst.rs1 <<"," << inst.rs2 <<" !!!Zero Register cannot be altered!!!"<< endl;
           }
            else 
            {
                //func code
             }
            
        }
        
                else if(inst.func == "slti")//34
        {
          
           if(register_File[inst.rd]==0)
           {
              cout << "Executed: " << inst.func << " " << inst.rd  <<","<< inst.rs1 <<"," << inst.imm <<" !!!Zero Register cannot be altered!!!"<< endl;
           }
            else 
            {
                //func code
             }
            
        }
        
                else if(inst.func == "sltu")//35
        {
          
           if(register_File[inst.rd]==0)
           {
               cout << "Executed: " << inst.func << " " << inst.rd  <<","<< inst.rs1 <<"," << inst.rs2 <<" !!!Zero Register cannot be altered!!!"<< endl;
           }
            else 
            {
                //func code
             }
            
        }
        
                  else if(inst.func == "sltiu")//36
        {
          
           if(register_File[inst.rd]==0)
           {
              cout << "Executed: " << inst.func << " " << inst.rd  <<","<< inst.rs1 <<"," << inst.imm <<" !!!Zero Register cannot be altered!!!"<< endl;
           }
            else 
            {
                //func code
             }
            
        }
        
                   else if(inst.func == "auipc")//37
        {
          
           if(register_File[inst.rd]==0)
           {
                cout << "Executed: " << inst.func << " " << inst.rd  <<","<< inst.imm <<" !!!Zero Register cannot be altered!!!"<< endl;
           }
            else 
            {
                //func code
             }
            
        }
        
          else if(inst.func == "fence")//38
        {
    
                //func code
            
        }
        
         
          else if(inst.func == "ecall")//39
        {
    
                //func code
            
        }
        
         
          else if(inst.func == "ebreak")//40
        {
    
                //func code
            
        }
        
        
    }
    // Output the current state of the registers
        cout << "Register File State after instruction:" << endl;
        for (const auto& reg : register_File) {
            cout << reg.first << " (r[" << reg.second << "]): " << r[reg.second] << endl;
        }
        cout << "------------------" << endl;
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
    vector<types> res = read(instructions);
   
    // Output the result for demonstration
    for (const auto& t : res) {
        cout << "label: " << t.label.first << " , func: " << t.func << ", rd: " << t.rd
             << ", rs1: " << t.rs1 << ", rs2: " << t.rs2 << ", imm: " << t.imm
             << ", branching_label: " << t.label_branching << endl;
    }
    
    Functions(res);


    return 0;
}
