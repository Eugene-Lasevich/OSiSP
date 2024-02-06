#!/usr/bin/env bash

calculate_star_points() {
    local r1=$1
    local r2=$2
    local n=$3

    local x_coords=()
    local y_coords=()

    for ((k=0; k<n; k++)); do
        angle1=$(echo "2 * 3.141592653589793 * $k / $n + $rotation_angle" | bc -l)
        angle2=$(echo "2 * 3.141592653589793 * $k / $n + 3.141592653589793 / $n + $rotation_angle" | bc -l)

        x1=$(echo "$r1 * c($angle1)" | bc -l)
        y1=$(echo "$r1 * s($angle1)" | bc -l)

        x2=$(echo "$r2 * c($angle2)" | bc -l)
        y2=$(echo "$r2 * s($angle2)" | bc -l)

        x1=$(echo "$x1 * 2 + 50" | bc -l)
        y1=$(echo "$y1 + 25" | bc -l)

        x2=$(echo "$x2 * 2 + 50" | bc -l)
        y2=$(echo "$y2 + 25" | bc -l)

        x_coords+=($(echo "$x1/1" | bc))
        y_coords+=($(echo "$y1/1" | bc))

        x_coords+=($(echo "$x2/1" | bc))
        y_coords+=($(echo "$y2/1" | bc))
    done

    local points=()
    local counter=1
    for ((i=0; i<${#x_coords[@]}; i++)); do
        points+=("${x_coords[i]},${y_coords[i]},$counter")
        ((counter++))
    done

    echo "${points[@]}"
}

generate_intermediate_points() {
    local points=("$@")
    local intermediate_points=()

    for ((i=0; i<${#points[@]}; i++)); do
        intermediate_points+=("${points[i]}")
        next_index=$(( (i+1) % ${#points[@]} ))

        IFS=',' read -r x1 y1 value1 <<< "${points[i]}"
        IFS=',' read -r x2 y2 value2 <<< "${points[next_index]}"
        mid_x=$(( (x1 + x2) / 2 ))
        mid_y=$(( (y1 + y2) / 2 ))
        mid_value=$((value1 + (value2 - value1) / 2))
        intermediate_points+=("$mid_x,$mid_y,$mid_value")
    done

    echo "${intermediate_points[@]}"
}

draw_star() {
    local points=("$@")
    for point in "${points[@]}"; do
        IFS=',' read -r x y value <<< "$point"
        tput cup $((y)) $((x))
        echo "*"
    done
}

read -p "Введите радиус внутренней окружности: " r1
read -p "Введите радиус внешней окружности: " r2
read -p "Введите количество лучей звезды: " n
clear
if [[ ! "$r1" =~ ^[0-9]+$ || ! "$r2" =~ ^[0-9]+$ || ! "$n" =~ ^[0-9]+$ || "$n" -lt 3 ]]; then
    echo "Ошибка: Введите положительные целые числа. Количество лучей должно быть не менее 3."
    exit 1
fi

rotation_angle=0
while true; do
    clear

    points=$(calculate_star_points $r1 $r2 $n)

    intermediate_points=$(generate_intermediate_points $points)

    points_array=($intermediate_points)
    draw_star "${points_array[@]}"

    rotation_angle=$(echo "$rotation_angle + 0.1" | bc -l)

    sleep 0.1
done

echo "Звезда отрисована в терминале."
