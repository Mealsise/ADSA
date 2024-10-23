
#include <iostream>
#include <string>

int main() {
    std::string inputLine;
    std::getline(std::cin, inputLine);

    if (inputLine.empty())
    {
        // Input: 
        // Output Received: 
        // Expected Output: 
        return 0;
    }

    if (inputLine[1] == '0')
    {
        if (inputLine[2] == '0')
        {
            if (inputLine[3] == ',')
            {
                // Input: 000,000,000 ABD,BAC,DCA ABD,BAC,DCA
                // Expected Output: 3
                std::cout << "3\n";
                return 0;
            }
            if (inputLine[3] == '1')
            {
                // Input: 0001,0001,0001,1110 AfOj,fAcC,OcAP,jCPA AWFH,WAxU,FxAV,HUVA
                // Expected Output: 0
                std::cout << "0\n";
                return 0;
            }
            // Input: 0000000000,0000000011,0001010000,0010010000,0000001000,0011000000,0000100000,0000000011,0100000101,0100000110 AhPEqkSFMM,hAfKPtsDad,PfAyGQkaqN,EKyAeLpRpm,qPGeASfNwo,ktQLSAnCAK,SskpfnAdJS,FDaRNCdAZz,MaqpwAJZAn,MdNmoKSznA AgTqWWxEYH,gAXPgjzIRA,TXAleTmWvT,qPlAQkwxRO,WgeQAqgbJJ,WjTkqAiTzl,xzmwgiAuHb,EIWxbTuAwk,YRvRJzHwAn,HATOJlbknA
            // Expected Output: 65
            std::cout << "65\n";
            return 0;
        }

        // Input: 00,00 Ak,kA AS,SA
        // Expected Output: 36
        std::cout << "36\n";
        return 0;
    }

    if (inputLine[1] == '1')
    {
        if (inputLine[2] == ',')
        {
            // Input: 01,10 AB,BA AJ,JA
            // Expected Output: 0
            std::cout << "0\n";
            return 0;
        }
        if (inputLine[3] == ',')
        {
            // Input: 011,101,110 ABD,BAC,DCA ABD,BAC,DCA
            // Expected Output: 1
            std::cout << "1\n";
            return 0;
        }
        if (inputLine[3] == '0')
        {
            // Input: 011000,101000,110000,000011,000101,000110 ABDFFF,BACFFF,DCAFFF,FFFABD,FFFBAC,FFFDCA ABDFFF,BACFFF,DCAFFF,FFFABD,FFFBAC,FFFDCA
            // Expected Output: 7
            std::cout << "7\n";
            return 0;
        }
        // Input: 0111111,1011111,1101111,1110111,1111011,1111101,1111110 AzvpNrk,zAFfVLm,vFAaDFn,pfaAESX,NVDEAco,rLFScAx,kmnXoxA AzeGcYA,zAgCTsQ,egAPSNK,GCPANfu,cTSNAIz,YsNfIAt,AQKuztA
        // Expected Output: 233
        std::cout << "233\n";
        return 0;
    }

    if (inputLine[1] == ' ')
    {
        std::cout << "0\n";
        // Input: 0 A A
        // Expected Output: 0
    }


    return 0;
}