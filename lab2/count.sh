#!/bin/bash

names=()
counts=()
prices=()

while IFS= read -r line || [[ -n $line ]]; do
    not_found=true
    IFS=' , ' read -r name count price <<<"${line}"

    re='^[0-9]+$'
    if ! [[ $count =~ $re ]]; then
        echo "ERROR: COUNT IS NOT A NUMBER" >&2
        exit 1
    fi

    if ! [[ $price =~ $re ]]; then
        echo "ERROR: PRICE IS NOT A NUMBER" >&2
        exit 1
    fi

    count=$((count))
    price=$((price))
    for j in "${!names[@]}"; do
        if [[ "${names[j]}" = "${name}" ]]; then
            counts[j]=$((count + counts[j]))
            prices[j]=$((price * count + prices[j]))
            not_found=false
            break
        fi
    done
    if $not_found; then
        names+=("$name")
        counts+=($((count)))
        prices+=($((price * count)))
    fi
done <input.txt

IFS=',' read -r name count price <<<"$input_string"

for i in "${!names[@]}"; do
    avg=$((prices[$i] / counts[$i]))
    echo "Наименование: ${names[$i]}, количество: ${counts[$i]}, средняя цена: ${avg}"
done