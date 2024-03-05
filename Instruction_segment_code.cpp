//Assembler
//Group mumbers :
// Name : Neha Dahire
// Name : Radha
// Name : Sarthak Dev Rathor
#include <bits/stdc++.h>
using namespace std;
#define int long long
set<string> s[6], sb;
map<string, string> ap, bp, cp, dp;
map<string, int> app;
int k;
int co = 0;
string R_form(string a, string b, string c, string d)
{
    string hlep = bp[a] + dp[d] + dp[c] + cp[a] + dp[b] + ap[a];
    bitset<32> bits(hlep);
    int n = bits.to_ulong();
    stringstream hexS;
    hexS << hex << setw(8) << setfill('0') << uppercase << n;
    hlep = hexS.str();
    hlep = "0x" + hlep;
    return hlep;
}
string S_form(string a, string b, string c)
{
    string d;
    d.clear();
    int i = 0;
    while (c[i] != '(')
        d += c[i++];
    string y;
    i++;
    while (c[i] != ')')
        y += c[i++];
    c = y;
    int n1 = stoi(d);
    bitset<12> bi(n1);
    string bis = bi.to_string();
    string bis2;
    bis2.clear();
    for (i = 7; i < 12; i++)
        bis2 += bis[i];
    string bis3;
    for (i = 0; i < 7; i++)
        bis3 += bis[i];
    i = 0;
    string hlep = bis3 + dp[b] + dp[c] + cp[a] + bis2 + ap[a];
    bitset<32> bits(hlep);
    int n = bits.to_ulong();
    stringstream hexS;
    hexS << hex << setw(8) << setfill('0') << uppercase << n;
    hlep = hexS.str();
    hlep = "0x" + hlep;
    return hlep;
}
string I_form(string a, string b, string c, string d)
{
    int n1 = stoi(d);
    bitset<12> bi(n1);
    string bis = bi.to_string();
    string hlep = bis + dp[c] + cp[a] + dp[b] + ap[a];
    bitset<32> bits(hlep);
    int n = bits.to_ulong();
    stringstream hexS;
    hexS << hex << setw(8) << setfill('0') << uppercase << n;
    hlep = hexS.str();
    hlep = "0x" + hlep;
    return hlep;
}
string U_form(string a, string b, string c)
{
   int n1 = stoi(c);
    bitset<32> bi(n1);
    string bis = bi.to_string();
    string bis2;
    for(int i=0;i<20;i++)bis2+=bis[i];
    string hlep = bis2 + dp[b]+ap[a];
    bitset<32> bits(hlep);
    int n = bits.to_ulong();
    stringstream hexS;
    hexS << hex << setw(8) << setfill('0') << uppercase << n;
    hlep = hexS.str();
    hlep = "0x" + hlep;
    return hlep;   
}
string UJ_form(string a, string b, string c)
{
    
}
string SB_form(string a, string b, string c, string d, const string &file1)
{ 
    int n1;
    ifstream file(file1);
    string line;
    string help;
    int y = 0;
    while (!file.eof())
    {
        int l = 0;
        string text;
        getline(file, text);
        int i = 0;
        while (text[i] == ' ')
            i++;
        if (text[i] == '#')
            continue;
        if (text[i] == '\0')
            continue;
        string a1;
        while (text[i] != ' ' && text[i] != ',' && text[i] != ':')
            a1 += text[i++];
        for (i = 0; i < 6; i++)
        {
            if (s[i].find(a1) == s[i].end())
                l++;
        }
        if (l == 6 && d == a1)
        {
            break;
        }
        y++;
    }
    file.close();
   // cout<<" "<<y<<" "<<co<<endl;
    n1 = (y- co-1)*4;
    if(n1<0)n1+=4;
    bitset<13> bi(n1);
    string bis = bi.to_string();
    string bis2, bis3;
    bis3 += bis[0];
    for (int i = 2; i < 8; i++)
        bis3 += bis[i];
    for (int i = 8; i < 12; i++)
        bis2 += bis[i];
    bis2 += bis[1];
    help = bis3 + dp[b] + dp[c] + cp[a] + bis2 + ap[a];
    bitset<32> bits(help);
    int n = bits.to_ulong();
    stringstream hexS;
    hexS << hex << setw(8) << setfill('0') << uppercase << n;
    help = hexS.str();
    help = "0x" + help;
    return help;
}

string decode(string str, const string &file1)
{
    string r;
    k=1;
    int i = 0;
    r.clear();
    while (str[i] == ' ')
        i++;
    while (str[i] != '#' && i < str.size())
        r += str[i++];
    string a, b, c, d;
    a.clear();
    c.clear();
    b.clear();
    d.clear();
    i = 0;
    while (r[i] != ' ' && r[i] != ',')
        a += r[i++];
    i++;
    while (r[i] != ' ' && r[i] != ',')
        b += r[i++];
    i++;
    while (r[i] != ' ' && r[i] != ',')
        c += r[i++];
    i++;
    while (r[i] != ' ' && r[i] != ',' && i < r.size())
        d += r[i++];
    string out;
    out.clear();
// cout<<a<<" "<<b<<" "<<c<<" "<<d;
    if (s[0].find(a) != s[0].end())
    {
        out = R_form(a, b, c, d);
    }
    else if (s[1].find(a) != s[1].end())
    {
        out = I_form(a, b, c, d);
    }
    else if (s[2].find(a) != s[2].end())
    {

        out = S_form(a, b, c);
    }
    else if (s[3].find(a) != s[3].end())
    {
        out = SB_form(a, b, c, d, file1);
    }
    else if (s[4].find(a) != s[4].end())
    {
        out = U_form(a, b, c);
    }
    else if (s[5].find(a) != s[5].end())
    {
        out = UJ_form(a, b, c);
    }

    else
    {
        out = "Instruction not identify";
        k++;
    }
    return out;
}

int32_t main()
{
    ap["add"] = "0110011";
    bp["add"] = "0000000";
    cp["add"] = "000";
    s[0].insert("add");

    ap["and"] = "0110011";
    bp["and"] = "0000000";
    cp["and"] = "111";
    s[0].insert("and");

    ap["or"] = "0110011";
    bp["or"] = "0000000";
    cp["or"] = "110";
    s[0].insert("or");

    ap["sll"] = "0110011";
    bp["sll"] = "0000000";
    cp["sll"] = "001";
    s[0].insert("sll");

    ap["slt"] = "0110011";
    bp["slt"] = "0000000";
    cp["slt"] = "010";
    s[0].insert("slt");

    ap["sra"] = "0110011";
    bp["sra"] = "0100000";
    cp["sra"] = "101";
    s[0].insert("sra");

    ap["srl"] = "0110011";
    bp["srl"] = "0000000";
    cp["srl"] = "101";
    s[0].insert("srl");

    ap["sub"] = "0110011";
    bp["sub"] = "0100000";
    cp["sub"] = "000";
    s[0].insert("sub");

    ap["xor"] = "0110011";
    bp["xor"] = "0000000";
    cp["xor"] = "100";
    s[0].insert("xor");

    ap["mul"] = "0110011";
    bp["mul"] = "0000001";
    cp["mul"] = "000";
    s[0].insert("mul");

    ap["div"] = "0110011";
    bp["div"] = "0000001";
    cp["div"] = "100";
    s[0].insert("div");

    ap["rem"] = "0110011";
    bp["rem"] = "0000001";
    cp["rem"] = "110";
    s[0].insert("rem");

    ap["addi"] = "0010011";
    cp["addi"] = "000";
    s[1].insert("addi");

    ap["andi"] = "0010011";
    cp["andi"] = "111";
    s[1].insert("andi");

    ap["jalr"] = "1100111";
    cp["jalr"] = "000";
    s[1].insert("jalr");

    ap["ori"] = "0010011";
    cp["ori"] = "110";
    s[1].insert("ori");

    ap["lb"] = "0000011";
    cp["lb"] = "000";
    s[1].insert("lb");

    ap["ld"] = "0000011";
    cp["ld"] = "011";
    s[1].insert("ld");

    ap["lh"] = "0000011";
    cp["lh"] = "001";
    s[1].insert("lh");

    ap["lw"] = "0000011";
    cp["lw"] = "010";
    s[1].insert("lw");

    ap["sb"] = "0100011";
    cp["sb"] = "000";
    s[2].insert("sb");

    ap["sw"] = "0100011";
    cp["sw"] = "010";
    s[2].insert("sw");

    ap["sh"] = "0100011";
    cp["sh"] = "001";
    s[2].insert("sh");

    ap["sd"] = "0100011";
    cp["sd"] = "011";
    s[2].insert("sd");

    ap["beq"] = "1100011";
    cp["beq"] = "000";
    s[3].insert("beq");

    ap["bne"] = "1100011";
    cp["bne"] = "001";
    s[3].insert("bne");

    ap["bge"] = "1100011";
    cp["bge"] = "101";
    s[3].insert("bge");

    ap["blt"] = "1100011";
    cp["blt"] = "100";
    s[3].insert("blt");

    ap["auipc"] = "0010111";
    s[4].insert("auipc");

    ap["lui"] = "0110111";
    s[4].insert("lui");

    ap["jal"] = "1101111";
    s[5].insert("jal");

    dp["x0"] = "00000";
    dp["x1"] = "00001";
    dp["x2"] = "00010";
    dp["x3"] = "00011";
    dp["x4"] = "00100";
    dp["x5"] = "00101";
    dp["x6"] = "00110";
    dp["x7"] = "00111";
    dp["x8"] = "01000";
    dp["x9"] = "01001";
    dp["x10"] = "01010";
    dp["x11"] = "01011";
    dp["x12"] = "01100";
    dp["x13"] = "01101";
    dp["x14"] = "01110";
    dp["x15"] = "01111";
    dp["x16"] = "10000";
    dp["x17"] = "10001";
    dp["x18"] = "10010";
    dp["x19"] = "10011";
    dp["x20"] = "10100";
    dp["x21"] = "10101";
    dp["x22"] = "10110";
    dp["x23"] = "10111";
    dp["x24"] = "11000";
    dp["x25"] = "11001";
    dp["x26"] = "11010";
    dp["x27"] = "11011";
    dp["x28"] = "11100";
    dp["x29"] = "11101";
    dp["x30"] = "11110";
    dp["x31"] = "11111";
    string file1 = "file1.asm";
    ifstream in("file1.asm");
    ofstream f("machine_code.mc");
    while (!in.eof())
    {
        int l = 0;
        string text;
        getline(in, text);
        int i = 0;
        while (text[i] == ' ')
            i++;
        if (text[i] == '#')
            continue;
        if (text[i] == '\0')
            continue;
        string a;
        while (text[i] != ' ' && text[i] != ',' && text[i] != ':')
            a += text[i++];
        for (i = 0; i < 6; i++)
        {
            if (s[i].find(a) == s[i].end())
                l++;
        }
        if (l == 6 && sb.find(a) == sb.end())
        {
            app[a] = k;
            sb.insert(a);
        }
        else if (l == 6 && sb.find(a) != sb.end())
        {
            f << "error in this line " << endl;
            return 0;
        }
    }
    in.close();
    in.open("file1.asm");
    while (!in.eof())
    {   k=1;
        int l = 0;
        string text;
        getline(in, text);
        int i = 0;
        while (text[i] == ' ')
            i++;
        if (text[i] == '#')
            continue;
        if (text[i] == '\0')
            continue;
        while (i < text.size())
        {
            if (text[i++] == ':')
            {
                l++;
                break;
            }
        }
        if (l)
            continue;
        string str = decode(text, file1);
        co++;
        f << str << endl;
        if (k == 0)
            return 0;
    }
    return 0;
}
