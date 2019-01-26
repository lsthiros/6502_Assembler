import json
import sys
from jinja2 import Template

def main():
    f = open(sys.argv[1])
    data = json.load(f)
    f.close()
    mode_list = data['AddressModes']
    num_modes = len(mode_list)
    all_ops = data['Ops']
    num_ops = len(all_ops)
    table = data['OpTable']

    all_codes = set()

    op_set = []
    for idx, op in enumerate(all_ops):
        op_item = {}
        op_item['name'] = op
        op_item['last'] = (idx == num_ops - 1)
        op_mode_list = []
        for mode_idx, mode in enumerate(mode_list):
            mode_item = {}
            if mode in table[op].keys():
                op_code = table[op][mode]
                if op_code in all_codes:
                    raise Exception("%s code has appeared more than once" % op_code)
                all_codes.add(op_code)
                mode_item['bytecode'] = op_code
                mode_item['valid'] = True
            else:
                mode_item['bytecode'] = "0"
                mode_item['valid'] = False
            mode_item['type'] = mode
            mode_item['last'] = (mode_idx == num_modes - 1)
            op_mode_list.append(mode_item)
        op_item['modes'] = op_mode_list
        op_set.append(op_item)
    
    with open('OpCodeTable.c.j2') as f:
        template = Template(f.read())
    final = template.render(op_list=op_set, num_ops=num_ops, num_modes=num_modes)

    with open('OpCodeTable.c', 'w') as f:
        f.write(final)

if __name__ == "__main__":
    main()
