// Assembler
// Group mumbers :
//  Name : Neha Dahire
//  Name : Radha
//  Name : Sarthak Dev Rathor
#include <bits/stdc++.h>
using namespace std;
#define int long long
// identify the instruction that where they belong
//  sb for lable repetition,register for identifing the register
set<string> s[7], sb, reg;
// opcode,fun7,fun3,registers
map<string, string> ap, bp, cp, dp;
// for error detcation
int k;
// for line count
int co = 0;
// Function to convert a hexadecimal string to binary string
string hexToBinary(const string &hexStr)
{
    // Convert hexadecimal string to decimal
    unsigned long long decimal = stoull(hexStr, nullptr, 16);

    // Convert decimal to binary string using a 64-bit representation
    string binaryStr = bitset<64>(decimal).to_string();

    // Find the position of the first non-zero bit in the binary string
    size_t firstNonZero = binaryStr.find_first_not_of('0');

    // If the binary string is all zeros, return "0"
    if (firstNonZero == string::npos)
    {
        return "0";
    }
    // Return the binary string from the first non-zero bit onward
    return binaryStr.substr(firstNonZero);
}
int binaryToDecimal(string binary) {
    int decimal = 0;
    int power = 0;

    // Start from the rightmost (least significant) digit
    for (int i = binary.size() - 1; i >= 0; --i) {
        if (binary[i] == '1') {
            decimal += pow(2, power);
        }
        if(binary[i]!='1'&&binary[i]!='0')
        return -2050;
        power++;
    }
    return decimal;
}
int hexCharToInt(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    } else if (c >= 'A' && c <= 'F') {
        return 10 + (c - 'A');
    } else if (c >= 'a' && c <= 'f') {
        return 10 + (c - 'a');
    } else {
        return -1; // Invalid character
    }
}
int hexToDecimal(string hex) {
    int decimal = 0;
    int power = 0;

    // Start from the rightmost (least significant) digit
    for (int i = hex.size() - 1; i >= 2; --i) {
        int digitValue = hexCharToInt(hex[i]);
        if (digitValue == -1) {
         //   cout <<i<<"  Invalid hexadecimal number." << endl;
            return -2050;
        }
        decimal += digitValue * pow(16, power);
        power++;
    }
    return decimal;
}

// Function to calculate the size of a binary string (number of bits)
int binarySize(string binaryStr)
{
    // Find the position of the first non-zero bit in the binary string
    size_t firstNonZero = binaryStr.find_first_not_of('0');

    // If the binary string is all zeros, return 0
    if (firstNonZero == string::npos)
    {
        return 0;
    }

    // Calculate and return the size of the binary string (number of bits)
    return binaryStr.length() - firstNonZero;
}
// R-format machine code generation function
int checkd(string a){
    int n =  a.size();
for(int i=0;i<n;i++){
    if((a[i]>'9'||a[i]<'0')&&a[i]!='-')return 0;
}
return 1;
}
string R_form(string a, string b, string c, string d)
{
    // Concatenate fields based on specified order
    string hlep = bp[a] + dp[d] + dp[c] + cp[a] + dp[b] + ap[a];

    // Convert binary to hexadecimal
    bitset<32> bits(hlep);
    int n = bits.to_ulong();
    stringstream hexS;
    hexS << hex << setw(8) << setfill('0') << uppercase << n;
    hlep = hexS.str();
    hlep = "0x" + hlep;
    return hlep;
}
// S-format machine code generation function
string S_form(string a, string b, string c)
{
    // Initialize offset and register strings
    string d;
    d.clear();
    int i = 0;
    // Extract offset from the input string
    while (c[i] != '(')
        d += c[i++];
    string y;
    i++;
// Extract register from the input string
    while (c[i] != ')')
        y += c[i++];
    
    c = y;
    // Check if the register is valid
    if (reg.find(c) == reg.end())
    {
        string hlep = "Register not found";
        k = 0;
        return hlep;
    }
    string bis;
    int deci;
    // Convert offset to binary if it is in hexadecimal format
    if (d[0] == '0' && d[1] == 'x')
    {
        bis = hexToBinary(d);
         deci = hexToDecimal(d);
    }
    else if(d[0] == '0' && d[1] == 'b'){
        bis = d;
        deci = binaryToDecimal(d);
    }
    else
    {
        // Convert offset to binary and ensure it fits within 12 bits
        int n1 = stoi(d);
        if(!checkd(d))
        return "OUT OF RANGE";
        deci = n1;
        bitset<12> bi(n1);
        bis = bi.to_string();
    }

    // Check if binary offset size is less than or equal to 12 bits
    if (deci<=2047 && deci>=-2048)
    {
        // Extract relevant bits from the binary offset
        string bis2;
        bis2.clear();
        for (i = 7; i < 12; i++)
            bis2 += bis[i];
        
        string bis3;
        for (i = 0; i < 7; i++)
            bis3 += bis[i];
        
        i = 0;

        // Concatenate fields and convert binary to hexadecimal
        string hlep = bis3 + dp[b] + dp[c] + cp[a] + bis2 + ap[a];
        bitset<32> bits(hlep);
        int n = bits.to_ulong();
        stringstream hexS;
        hexS << hex << setw(8) << setfill('0') << uppercase << n;
        hlep = hexS.str();
        hlep = "0x" + hlep;
        return hlep;
    }
    else
        return "OUT OF RANGE";
}
// Load Immediate (L_I) format machine code generation function
string L_I_form(string a, string b, string c)
{
    // Variables for extracting offset and register from the instruction
    string d;
    d.clear();
    int i = 0;

    // Extracting offset from the instruction
    while (c[i] != '(')
        d += c[i++];
    
    string y;
    i++;

    // Extracting register from the instruction
    while (c[i] != ')')
        y += c[i++];
    
    c = y;

    // Check if the register is valid
    if (reg.find(c) == reg.end())
    {
        string hlep = "Register not found";
        k = 0;
        return hlep;
    }

    string bis;
    int deci;
    //cout << d << endl;
    // Convert offset to binary if it is in hexadecimal format
    if (d[0] == '0' && d[1] == 'x')
    {
        bis = hexToBinary(d);
        deci = hexToDecimal(d);
    }
    else if(d[0] == '0' && d[1] == 'b'){
        bis = d;
        deci = binaryToDecimal(d);
    }
    else
    {
        // Convert offset to binary and ensure it fits within 12 bits
        int n1 = stoi(d);
         if(!checkd(d))
        return "OUT OF RANGE";
        deci = n1;
        bitset<12> bi(n1);
        bis = bi.to_string();
    }

    // Check if binary offset size is less than or equal to 12 bits
    if (deci<=2047 && deci>=-2048)
    {
        // Concatenate fields and convert binary to hexadecimal
        string hlep = bis + dp[c] + cp[a] + dp[b] + ap[a];
        bitset<32> bits(hlep);
        int n = bits.to_ulong();
        stringstream hexS;
        hexS << hex << setw(8) << setfill('0') << uppercase << n;
        hlep = hexS.str();
        hlep = "0x" + hlep;
        return hlep;
    }
    else
        return "OUT OF RANGE";
}
// I-format machine code generation function
string I_form(string a, string b, string c, string d)
{
    // Convert immediate value to binary
    string bis;
    int deci;
   // cout << d << endl;
    if (d[0] == '0' && d[1] == 'x')
    {
        // If immediate value is in hexadecimal, convert to binary
        bis = hexToBinary(d);
        deci = hexToDecimal(d);
    }
    else if(d[0] == '0' && d[1] == 'b'){
        bis = d;
        deci = binaryToDecimal(d);
    }
    else
    {
        // If immediate value is in decimal, convert to binary and ensure it fits within 12 bits
        int n1 = stoi(d);
         if(!checkd(d))
        return "OUT OF RANGE";
        deci = n1;
        bitset<12> bi(n1);
        bis = bi.to_string();
    }

    // Check if binary immediate size is less than or equal to 12 bits
    if (deci<=2047 && deci>=-2048)
    {
        // Concatenate fields and convert binary to hexadecimal
        string hlep = bis + dp[c] + cp[a] + dp[b] + ap[a];
        bitset<32> bits(hlep);
        int n = bits.to_ulong();
        stringstream hexS;
        hexS << hex << setw(8) << setfill('0') << uppercase << n;
        hlep = hexS.str();
        hlep = "0x" + hlep;
        return hlep;
    }
    else
        return "OUT OF RANGE";
}

// U-format machine code generation function
string U_form(string a, string b, string c)
{
    // Convert immediate value to binary
    string bis;
    int deci;
    int n1 = stoi(c);
    int n2 = n1;
    if (c[0] == '0' && c[1] == 'x')
    {
        // If immediate value is in hexadecimal, convert to binary
        bis = hexToBinary(c);
        deci = hexToDecimal(c);
    }
    else if(c[0] == '0' && c[1] == 'b'){
        bis = c;
        deci = binaryToDecimal(c);
    }
    else
    {   
         if(!checkd(c))
        return "OUT OF RANGE";
        // If immediate value is in decimal, convert to binary and ensure it fits within 32 bits
        bitset<32> bi(n1);
        deci = n1;
        bis = bi.to_string();
    }
   // cout << bis << endl;
    string bis2;
    for (int i = 12; i <32; i++)
        bis2 += bis[i];

    // Extract the most significant 20 bits from the binary immediate value
   
  //  cout << bis2 << endl;

    // Concatenate fields and convert binary to hexadecimal
    if(deci>=0 && deci<=1048575 && n2>=0 && n2<=1048575){
    
    string hlep = bis2 + dp[b] + ap[a];
    bitset<32> bits(hlep);
    int n = bits.to_ulong();
    stringstream hexS;
    hexS << hex << setw(8) << setfill('0') << uppercase << n;
    hlep = hexS.str();
    hlep = "0x" + hlep;
    return hlep;
    }
    else
        return "OUT OF RANGE";
}
// UJ-format machine code generation function
string UJ_form(string a, string b, string c, const string &file1)
{
    int n1;
    ifstream file(file1);

    // Variables for reading file
    string help;
    int y = 0;
    int no = 0;

    // Read lines from the file
    while (!file.eof())
    {
        int l = 0;
        string text;
        getline(file, text);
        int i = 0;

        // Skip leading spaces
        while (text[i] == ' ')
            i++;

        // Skip lines starting with '#' or empty lines
        if (text[i] == '#')
            continue;
        if (text[i] == '\0')
            continue;

        // Extract the label or instruction mnemonic
        string a1;
        while (text[i] != ' ' && text[i] != ',' && text[i] != ':')
            a1 += text[i++];

        // Check if the label is found in the symbol table
        for (i = 0; i < 7; i++)
        {
            if (s[i].find(a1) == s[i].end())
                l++;
        }

        // If the label is found and matches the target label, break the loop
        if (l == 7 && c == a1)
        {
            no++;
            break;
        }

        // If the label is not found, continue searching
        if (l == 7)
            continue;

        y++;
    }

    // If the label is not found, return an error message
    if (no == 0)
    {
        k = 0;
        return "Label not found";
    }

    // Calculate the offset based on the line number
    file.close();
    n1 = (y - co) * 4;

    // Extract relevant bits from the offset and concatenate fields
    bitset<32> bi(n1);
    string bis = bi.to_string();
    string bis2;
    bis2 += bis[11];
    for (int i = 21; i <= 30; i++)
        bis2 += bis[i];
    bis2 += bis[20];
    for (int i = 12; i <= 19; i++)
        bis2 += bis[i];

    // Concatenate fields and convert binary to hexadecimal
    help = bis2 + dp[b] + ap[a];
    bitset<32> bits(help);
    int n = bits.to_ulong();
    stringstream hexS;
    hexS << hex << setw(8) << setfill('0') << uppercase << n;
    help = hexS.str();
    help = "0x" + help;
    return help;
}

// SB-format machine code generation function
string SB_form(string a, string b, string c, string d, const string &file1)
{
    int n1;
    ifstream file(file1);

    // Variables for reading file
    string help;
    int y = 0;
    int no = 0;

    // Read lines from the file
    while (!file.eof())
    {
        int l = 0;
        string text;
        getline(file, text);
        int i = 0;

        // Skip leading spaces
        while (text[i] == ' ')
            i++;

        // Skip lines starting with '#' or empty lines
        if (text[i] == '#')
            continue;
        if (text[i] == '\0')
            continue;

        // Extract the label or instruction mnemonic
        string a1;
        while (text[i] != ' ' && text[i] != ',' && text[i] != ':')
            a1 += text[i++];

        // Check if the label is found in the symbol table
        for (i = 0; i < 7; i++)
        {
            if (s[i].find(a1) == s[i].end())
                l++;
        }

        // If the label is found and matches the target label, break the loop
        if (l == 7 && d == a1)
        {
            no++;
            break;
        }

        // If the label is not found, continue searching
        if (l == 7)
            continue;

        y++;
    }

    // If the label is not found, return an error message
    file.close();
    if (no == 0)
    {
        k = 0;
        return "Label not found";
    }

    // Calculate the offset based on the line number
    n1 = (y - co) * 4;

    // Extract relevant bits from the offset and concatenate fields
    bitset<13> bi(n1);
    string bis = bi.to_string();
    string bis2, bis3;
    bis3 += bis[0];
    for (int i = 2; i < 8; i++)
        bis3 += bis[i];
    for (int i = 8; i < 12; i++)
        bis2 += bis[i];
    bis2 += bis[1];

    // Concatenate fields and convert binary to hexadecimal
    help = bis3 + dp[c] + dp[b] + cp[a] + bis2 + ap[a];
    bitset<32> bits(help);
    int n = bits.to_ulong();
    stringstream hexS;
    hexS << hex << setw(8) << setfill('0') << uppercase << n;
    help = hexS.str();
    help = "0x" + help;
    return help;
}
// Decode function to convert assembly instruction to machine code
string decode(string str, const string &file1)
{
    // Initialize variables
    string r;
    k = 1; // Flag indicating successful decoding
    int i = 0;
    r.clear();

    // Remove leading spaces
    while (str[i] == ' ')
        i++;

    // Extract the instruction or label from the input string
    while (str[i] != '#' && i < str.size())
        r += str[i++];
   // cout<<r<<endl;
    // Initialize fields for opcode and operands
    string a, b, c, d;
    a.clear();
    c.clear();
    b.clear();
    d.clear();
    i = 0;

    // Extract opcode and operands from the instruction
    while (r[i] != ' ' && r[i] != ',' && r[i] != '\0')
        a += r[i++];
       // cout<<r[i]<<" ";
       i++;
    while(r[i]==' ')i++;
    ///cout<<r[i]<<endl;
    while (r[i] != ' ' && r[i] != ',' && r[i] != '\0')
        b += r[i++];
        i++;
    while(r[i]==' ')i++;
    while (r[i] != ' ' && r[i] != ',' && r[i] != '\0')
        c += r[i++];
        i++;
    while(r[i]==' ')i++;
    while (r[i] != ' ' && r[i] != ',' && r[i]!='\0')
        d += r[i++];
    //cout<<" "<<c<<" "<<d<<endl;
    // Initialize output string
  //  cout<<a<<" "<<b<<" "<<c<<" "<<d<<endl;
  //cout<<d.size()<<endl;
    string out;
    out.clear();

    // Decode the instruction based on its opcode
    if (s[0].find(a) != s[0].end())
    {
        // R-format instruction
        if (reg.find(c) == reg.end() || reg.find(b) == reg.end() || reg.find(d) == reg.end())
        {
            out = "Register not found";
            k = 0;
            return out;
        }
        out = R_form(a, b, c, d);
    }
    else if (s[1].find(a) != s[1].end())
    {
        // I-format instruction
        if (reg.find(c) == reg.end() || reg.find(b) == reg.end())
        {
            out = "Register not found";
            k = 0;
            return out;
        }
        out = I_form(a, b, c, d);
    }
    else if (s[2].find(a) != s[2].end())
    {
        // S-format instruction
        if (reg.find(b) == reg.end())
        {
            out = "Register not found";
            k = 0;
            return out;
        }
        out = S_form(a, b, c);
    }
    else if (s[3].find(a) != s[3].end())
    {
        // SB-format instruction
        if (reg.find(c) == reg.end() || reg.find(b) == reg.end())
        {
            out = "Register not found";
            k = 0;
          //  cout<<c<<endl;
            return out;
        }
        out = SB_form(a, b, c, d, file1);
    }
    else if (s[4].find(a) != s[4].end())
    {
        // U-format instruction
        if (reg.find(b) == reg.end())
        {
            out = "Register not found";
            k = 0;
            return out;
        }
        out = U_form(a, b, c);
    }
    else if (s[5].find(a) != s[5].end())
    {
        // UJ-format instruction
        if (reg.find(b) == reg.end())
        {
            out = "Register not found";
            k = 0;
            return out;
        }
        out = UJ_form(a, b, c, file1);
    }
    else if (s[6].find(a) != s[6].end())
    {
        // L_I-format instruction
        if (reg.find(b) == reg.end())
        {
            out = "Register not found";
            k = 0;
            return out;
        }
        out = L_I_form(a, b, c);
    }
    else
    {  // cout<<a<<endl;
        // Unrecognized instruction
        out = "Instruction not identified";
        k = 0;
    }

    // Check for decoding errors
    if (out == "ERROR")
        k = 0;

    return out;
}
int32_t main()
{
    // Initialize registers
reg = {"x0", "x1", "x2", "x3", "x4", "x5", "x6", "x7", "x8", "x9", "x10", "x11", "x12", "x13", "x14", "x15", "x16", "x17", "x18", "x19", "x20", "x21", "x22", "x23", "x24", "x25", "x26", "x27", "x28", "x29", "x30", "x31"};

// Initialize dp for registers
for (int i = 0; i < 32; ++i) {
    string regName = "x" + to_string(i);
    dp[regName] = bitset<5>(i).to_string();
}
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

    ap["slli"] = "0010011";
    cp["slli"] = "001";
    s[1].insert("slli");

    ap["ori"] = "0010011";
    cp["ori"] = "110";
    s[1].insert("ori");

    ap["lb"] = "0000011";
    cp["lb"] = "000";
    s[6].insert("lb");

    ap["ld"] = "0000011";
    cp["ld"] = "011";
    s[6].insert("ld");

    ap["lh"] = "0000011";
    cp["lh"] = "001";
    s[6].insert("lh");

    ap["lw"] = "0000011";
    cp["lw"] = "010";
    s[6].insert("lw");

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
    // Open input file ("file1.asm") for reading and output file ("machine_code.mc") for writing
string file1 = "file1.asm";
ifstream in("file1.asm");
ofstream f("machine_code.mc");

// First pass to identify labels and handle errors
while (!in.eof())
{
    int l = 0;
    string text;
    getline(in, text);
    int i = 0;

    // Skip leading spaces
    while (text[i] == ' ')
        i++;

    // Ignore lines starting with '#'
    if (text[i] == '#')
        continue;

    // Ignore empty lines
    if (text[i] == '\0')
        continue;

    // Extract the opcode or label from the line
    string a;
    while (text[i] != ' ' && text[i] != ',' && text[i] != ':')
        a += text[i++];

    // Check if the opcode or label is not found in any instruction set
    for (i = 0; i < 7; i++)
    {
        if (s[i].find(a) == s[i].end())
            l++;
    }

    // If not found and it's a new label, add it to the set; otherwise, report an error
    if (l == 7 && sb.find(a) == sb.end())
    {
        sb.insert(a);
    }
    else if (l == 7 && sb.find(a) != sb.end())
    {
        // Print error message and return 0
        f << "error in this line " << endl;
        return 0;
    }
}

// Close the input file and reopen for the second pass
in.close();
in.open("file1.asm");

int pc = 0; // Program counter
string p_c; // String to hold hex representation of the program counter

// Second pass to generate machine code
while (!in.eof())
{
    k = 1;
    int l = 0;
    string text;
    getline(in, text);
    int i = 0;

    // Skip leading spaces
    while (text[i] == ' ')
        i++;

    // Ignore lines starting with '#'
    if (text[i] == '#')
        continue;

    // Ignore empty lines
    if (text[i] == '\0')
        continue;

    // Check for label and skip it
    while (i < text.size())
    {
        if (text[i++] == ':')
        {
            l++;
            break;
        }
    }
    if(l){
            string hlep2;
            int j=0;
            while(text[j++]!=':');
            //cout<<text<<" "<<endl;
            while(text[j]!='\0'&&text[j]!='#')hlep2+=text[j++];
            hlep2+='\0';
            text = hlep2;
           // cout<<text<<" ";
            j=0;
            while(text[j++]==' ');
           // cout<<;
            if(text[j]!='\0'){
                l=0;
              //  cout<<text<<" ";
            }
        }
    // If it's not a label line, decode the instruction and generate machine code
    
    if (l == 0)
    {
        string str = decode(text, file1);
        if(str=="ERROR"){
            f << str << endl;
            break;
        }
        co++;
        if(str=="OUT OF RANGE"){
            f << str << endl;
            break;
        }
        // Convert program counter to hex and format
        stringstream hexS;
        hexS << hex << pc;
        p_c = hexS.str();
        p_c = "0x" + p_c;

        // Write the program counter and machine code to the output file
        f << p_c << "  ";
        f << str << endl;

        // Update the program counter
        pc += 4;

        // If an error occurred during decoding, return 0
        if (k == 0)
            return 0;
    }
}

// Close the input and output files
in.close();
f.close();

// Return 0 indicating successful execution
return 0;
}
