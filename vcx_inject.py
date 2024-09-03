# manually inject cheez source references into zdoom.vcxproj
# there's definitely a better way to do this, but I don't negotiate with terrorists
import os.path

proj_file = "src/zdoom.vcxproj"
filters_file = "src/zdoom.vcxproj.filters"

cpp_inc = '<ClCompile Include="cheez.cpp">\n<PrecompiledHeader>NotUsing</PrecompiledHeader>\n</ClCompile>'
h_inc = '<ClInclude Include="cheez.h" />'

cpp_filter = '<ClInclude Include="cheez.cpp">\n<Filter>Source Files</Filter>\n</ClInclude>'
h_filter = '<ClInclude Include="cheez.h">\n<Filter>Header Files</Filter>\n</ClInclude>'

def write_vcxproj(proj_file):
    if not os.path.isfile(proj_file):
        print("[X] Can't find ZDOOM vcxproj file")
        exit()

    with open(proj_file,"r") as f:
        proj_content = f.read()
        if "cheez" in proj_content:
            print("[!] vcxproj has already been injected. Skipping...")
            return
        proj_content = proj_content.split("\n")

    idx = 0
    for line_num in range(0,len(proj_content)):
        line = proj_content[line_num]
        if ("<ClInclude" in line): 
            idx = line_num
            break

    proj_content.insert(idx,cpp_inc)
    proj_content.insert(idx,h_inc)

    with open(proj_file,"w") as f:
        for line in proj_content:
            f.write(line + "\n")

    print("zdoom.vcxproj done.")

def write_vcxfilters(filters_file):
    if not os.path.isfile(filters_file):
        print("[X] Can't find ZDOOM vcxproj.filters file")
        exit()

    with open(filters_file,"r") as f:
       filters_content = f.read()
       if "cheez" in filters_content:
           print("[!] vcxproj.filters has already been injected. Skipping...")
           return
       filters_content = filters_content.split("\n")

    cnt = 0
    trans_filters_content = filters_content
    for line_num in range(0,len(filters_content)):
        line = filters_content[line_num]
        if ("<ItemGroup>" in line):
            cnt += 1
            if cnt == 1: # source file
                trans_filters_content.insert(line_num+1,cpp_filter)
            elif cnt == 2: # header file
                trans_filters_content.insert(line_num+1,h_filter)
                break
                
    with open(filters_file,"w") as f:
        for line in trans_filters_content:
            f.write(line + "\n")

    print("zdoom.vcxproj.filters done.")


if __name__ == "__main__":
    write_vcxproj(proj_file)
    write_vcxfilters(filters_file)
