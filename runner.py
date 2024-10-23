import subprocess
test_cases = [("", ""),("000,000,000 ABD,BAC,DCA ABD,BAC,DCA", "3"),("0001,0001,0001,1110 AfOj,fAcC,OcAP,jCPA AWFH,WAxU,FxAV,HUVA", "0"),("0000000000,0000000011,0001010000,0010010000,0000001000,0011000000,0000100000,0000000011,0100000101,0100000110 AhPEqkSFMM,hAfKPtsDad,PfAyGQkaqN,EKyAeLpRpm,qPGeASfNwo,ktQLSAnCAK,SskpfnAdJS,FDaRNCdAZz,MaqpwAJZAn,MdNmoKSznA AgTqWWxEYH,gAXPgjzIRA,TXAleTmWvT,qPlAQkwxRO,WgeQAqgbJJ,WjTkqAiTzl,xzmwgiAuHb,EIWxbTuAwk,YRvRJzHwAn,HATOJlbknA", "65"),("00,00 Ak,kA AS,SA", "36"),("01,10 AB,BA AJ,JA", "0"),("011,101,110 ABD,BAC,DCA ABD,BAC,DCA", "1"),("011000,101000,110000,000011,000101,000110 ABDFFF,BACFFF,DCAFFF,FFFABD,FFFBAC,FFFDCA ABDFFF,BACFFF,DCAFFF,FFFABD,FFFBAC,FFFDCA", "7"),("0111111,1011111,1101111,1110111,1111011,1111101,1111110 AzvpNrk,zAFfVLm,vFAaDFn,pfaAESX,NVDEAco,rLFScAx,kmnXoxA AzeGcYA,zAgCTsQ,egAPSNK,GCPANfu,cTSNAIz,YsNfIAt,AQKuztA", "233"),("0 A A", "0")]
for i, (input_data, expected_output) in enumerate(test_cases):
    process = subprocess.Popen(["./a.out"], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    actual_output, error_output = process.communicate(input=input_data)
    actual_output = actual_output.strip()
    expected_output = expected_output.strip()
    if actual_output == expected_output:
        print(f"Test case {i + 1}: Passed")
    else:
        print(f"Test case {i + 1}: Failed")
        print(f"  Input: {input_data}")
        print(f"  Expected Output: {expected_output}")
        print(f"  Actual Output: {actual_output}")
        if error_output:
            print(f"  Error Output: {error_output}")