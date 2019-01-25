import json
import sys

def main():
    f = open(sys.argv[1])
    data = json.load(f)
    f.close()
    mode_list = data['AddressModes']
    all_ops = data['Ops']
    table = data['OpTable']

    all_codes = set()

    for op in all_ops:
        print("/* %s */" % op)
        print("{")
        for mode in mode_list:
            if mode in table[op].keys():
                op_code = table[op][mode]
                if op_code in all_codes:
                    raise Exception("%s code has appeared more than once" % op_code)
                all_codes.add(op_code)
                print("    %s, /* %s */" % (op_code, mode))
            else:
                print("    0,    /* %s not valid */" % mode)
        print("},")


if __name__ == "__main__":
    main()
