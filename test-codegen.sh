#!/bin/sh

_red='\033[1;31m'
_green='\033[1;32m'
_reset='\033[0m'

rm cool-codegen
make cool-codegen

if [ $? -gt 0 ]; then
  exit 1
fi

TEST_FILE_DIR=codegen-test-files
infiles=$(ls ${TEST_FILE_DIR}/*.cl)
cnt=$((0))
correct_cnt=$((0))
for infile in $infiles; do
  ./cool-codegen ${infile}
  spim -file "codegenout.s" > test.out
  tail -n +2 test.out |\
    awk '{
            reg= "\/?.*:[0-9]+";
            sub(reg, "", $0)
            print $0
         }' > A
  tail -n +6 "${infile}.out" |\
    awk '{
            reg= "\/?.*:[0-9]+";
            sub(reg, "", $0)
            print $0
         }' > B

  diff -y --suppress-common-lines A B > diff.out
  if [ $? -eq 0 ]; then
    correct_cnt=$((correct_cnt+1))
    echo "[${_green}PASS${_reset}]\t$infile"
  else
    echo "[${_red}FAILE${_reset}]\t$infile"
    echo "-----------------------------------------------------------------"
    echo "left column is mycodegen output, right column is correct output"
    echo "-----------------------------------------------------------------"
    cat diff.out
    echo "-----------------------------------------------------------------"
    echo "press any key to continue"
    read answer
  fi

  cnt=$((cnt+1))
done

echo ""
echo "[cool-codegen Score] ${correct_cnt}/${cnt}"

rm A B diff.out test.out
