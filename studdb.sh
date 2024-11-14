#!/bin/bash



# Array to store records in the format "ID,name,grade"

declare -a student_records



show_menu() {

    echo "Select an operation:"

    echo "a) Insert a record"

    echo "b) Delete a record"

    echo "c) Update a record"

    echo "d) Search for a record"

    echo "e) Display all records"

    echo "f) Exit"

    read -p "Enter your choice: " choice

}



insert_record() {

    read -p "Enter Student ID: " id

    read -p "Enter Student Name: " name

    read -p "Enter Student Grade: " grade

    student_records+=("$id,$name,$grade")  # Add the new record to the array

    echo "Record inserted successfully."

}



delete_record() {

    read -p "Enter Student ID to delete: " id

    found=0

    for i in "${!student_records[@]}"; do

        # Check if the record starts with the given ID

        if [[ ${student_records[$i]} == $id,* ]]; then

            unset 'student_records[$i]'  # Remove the record from the array

            found=1

            echo "Record with ID $id deleted successfully."

            break

        fi

    done

    if [ $found -eq 0 ]; then

        echo "Record with ID $id not found."

    fi

}



update_record() {

    read -p "Enter Student ID to update: " id

    found=0

    for i in "${!student_records[@]}"; do

        # Check if the record starts with the given ID

        if [[ ${student_records[$i]} == $id,* ]]; then

            read -p "Enter new Student Name: " name

            read -p "Enter new Student Grade: " grade

            student_records[$i]="$id,$name,$grade"  # Update the record in the array

            found=1

            echo "Record with ID $id updated successfully."

            break

        fi

    done

    if [ $found -eq 0 ]; then

        echo "Record with ID $id not found."

    fi

}



search_record() {

    read -p "Enter Student ID to search: " id

    found=0

    for record in "${student_records[@]}"; do

        # Check if the record starts with the given ID

        if [[ $record == $id,* ]]; then

            echo "Record found: $record"

            found=1

            break

        fi

    done

    if [ $found -eq 0 ]; then

        echo "Record with ID $id not found."

    fi

}



display_records() {

    if [ ${#student_records[@]} -eq 0 ]; then

        echo "No records available."

    else

        echo "Current Records:"

        for record in "${student_records[@]}"; do

            echo "$record"

        done

    fi

}



while true; do

    show_menu

    case $choice in

        a|A) insert_record ;;

        b|B) delete_record ;;

        c|C) update_record ;;

        d|D) search_record ;;

        e|E) display_records ;;

        f|F) echo "Exiting..."; exit 0 ;;

        *) echo "Invalid option. Please try again." ;;

    esac

done