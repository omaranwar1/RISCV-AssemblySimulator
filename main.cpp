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
class types {
public:
    string label, func, rs1, rs2, rd, imm, label_branching,shamt,j_label;
     
};

vector<types> read(vector<string> x) {
    vector<types> result;

    for (auto& str : x) {
        stringstream ss(str);
        string first_word, rd, rs1, rs2, imm, label_bran, shamt,jumping_label;
        types t;
        
        // Extract first word from the string
        ss >> first_word;

        // Check if there is a label or not
        if (first_word.back() == ':') {
            t.label = first_word.substr(0, first_word.size() - 1);//add label
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
        }
        // Check if the function is I-type
        else if(find(I_type.begin(),I_type.end(),t.func) != I_type.end()) {
            getline(ss, rd, ',');
            getline(ss, rs1, ',');
            ss >> imm;

            // Assign the destination, source, and immediate
            t.rd = rd.substr(rd.find(' ') + 1);
            t.rs1 = rs1.substr(rs1.find(')')+1 );
            t.imm = imm;

            result.push_back(t);
        }
        else if(find(I_type2.begin(),I_type2.end(),t.func)!=I_type2.end())
        {
           getline(ss, rd, ',');
           getline(ss, imm, '('); //imm won't include any paranthesis
           ss >> rs1;//rs1 will include the closing paranthesis
           ss.ignore();

    
          t.rd = rd.substr(rd.find(' ') + 1);
          t.imm = imm;
          t.rs1 = rs1.substr(0, rs1.find(')'));

          result.push_back(t);
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
        }
        else if(find(S_type.begin(),S_type.end(),t.func)!=S_type.end())
        {
           getline(ss, rs1, ',');
           getline(ss, imm, '('); //imm won't include any paranthesis
           ss >> rs2;//rs1 will include the closing paranthesis
           ss.ignore();

    
          t.rs1 = rs1.substr(rs1.find(' ') + 1);
          t.imm = imm;
          t.rs2 = rs2.substr(0, rs2.find(')'));

          result.push_back(t);
        }
        else if(find(jump_link.begin(), jump_link.end(),t.func)!=jump_link.end())
        {
           getline(ss, rd, ',');
           getline(ss, imm, '('); //imm won't include any paranthesis
           ss >> rs1;//rs1 will include the closing paranthesis
           ss.ignore();

    
          t.rd = rd.substr(rd.find(' ') + 1);
          t.imm = imm;
          t.rs1 = rs1.substr(0, rs1.find(')'));
          result.push_back(t);
        }
        else if(find(jump2.begin(), jump2.end(),t.func)!=jump2.end())
        {
            getline(ss,rd,',');
            ss>>jumping_label;
            t.rd = rd.substr(rd.find(' ') + 1);
            t.j_label=jumping_label;
            result.push_back(t);
            
        }
        else if(find(shifiting.begin(),shifiting.end(),t.func) != shifiting.end()) {
            getline(ss, rd, ',');
            getline(ss, rs1, ',');
            ss >> shamt;

            // Assign the destination, source, and immediate
            t.rd = rd.substr(rd.find(' ') + 1);
            t.rs1 = rs1.substr(rs1.find(')')+1 );
            t.shamt = shamt;

            result.push_back(t);
        }
        else if(find(lower_upperImm.begin(), lower_upperImm.end(),t.func)!=lower_upperImm.end())
        {
            getline(ss,rd,',');
            ss>>imm;
            t.rd = rd.substr(rd.find(' ') + 1);
            t.imm=imm;
            result.push_back(t);
            
        }
    }

    return result;
}


int main() {
    
    vector<string> x = {"loop: sll x16,x20,x4", "t1: addi x5,x5,2", "t3: lw t0,4(t1)","bge s0,s3,exit1","sw t0,6(t1)", "exist: jalr x0,4(ra)", "slli x10,x5,2","jal x0,func2","lui x0,0x12345"};
    vector<types> res = read(x);

    // Output the result for demonstration
    for (auto& t : res)
    {
        cout<<"label:"<<t.label<<" , func:"<<t.func<<", rd:"<< t.rd<<", rs1:"<<t.rs1<<", rs2:"<<t.rs2<<", imm:"<<t.imm<<",branching_label:"<<t.label_branching<<", shamt:"<<t.shamt<<", jump:"<<t.j_label<<endl;
    }
       

    return 0;
}
