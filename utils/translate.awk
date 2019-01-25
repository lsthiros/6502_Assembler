# Many websites use this notation to specify address modes and codes
# This converts the tables from https://en.wikibooks.org/wiki/6502_Assembly#Absolute:_a
# to the json format in ByteCodes.json
{
mode["A"] = "ACCUMULATOR"
mode["a"] = "ABSOLUTE"
mode["a,x"] = "ABS_X"
mode["a,y"] = "ABS_Y"
mode["#"] = "IMMEDIATE"
mode["zp"] = "ZP_REL"
mode["r"] = "ZP_REL"
mode["(zp,x)"] = "INDEX_IND"
mode["zp,x"] = "ZP_X"
mode["zp,y"] = "ZP_Y"
mode["(zp),y"] = "IND_INDEX";

    print "\"" mode[$1] "\": \"0x" $2 "\","
}
