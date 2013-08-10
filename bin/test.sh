#!/bin/sh

# while :
# do
#     ./shuffle < input.txt >> result.txt
#     sleep 2
# done


awk -F'\t' '{
  a[$0]++;
}
END{
  for(item in a)
    printf("%s:%d\n", item, a[item])
}' result.txt
