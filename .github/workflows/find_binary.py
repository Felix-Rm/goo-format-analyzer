import os
import sys

possible_bin_names = {"goo_format_analyzer", "goo_format_analyzer.exe"}
platforms = {"linux": "linux", "darwin": "macos", "win32": "windows"}

root_dir = os.path.abspath('.')

binary_abs = None
for root, dirs, files in os.walk(root_dir):
    binary_dir_content = set(files) & possible_bin_names
    if binary_dir_content:
        binary_abs = os.path.join(root, binary_dir_content.pop())
        break

binary_filename = os.path.basename(binary_abs)
binary_base, binary_ext = os.path.splitext(binary_filename)
binary_filename_os = binary_base + '_' + platforms[sys.platform] + binary_ext

with open(os.environ['GITHUB_OUTPUT'], 'a') as f:
    f.write(f'binary_filename={binary_filename}\n')
    f.write(f'binary_filename_os={binary_filename_os}\n')
    f.write(f'binary_abs_path={binary_abs}\n')