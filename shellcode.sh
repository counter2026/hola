1.if else
Code-
 
#!/bin/bash
echo "Enter a number: "
read number
 
if [ $number -gt 0 ]; then
    echo "The number is positive."
elif [ $number -lt 0 ]; then
    echo "The number is negative."
else
    echo "The number is zero."
fi
 
 
2.for loop
Code-
#!/bin/bash
echo "Enter a number: "
read number
is_prime=1
for ((i=2; i<=number/2; i++))
do
    if [ $((number%i)) -eq 0 ]; then
        is_prime=0
        break
    fi
done
if [ $number -eq 1 ]; then
    echo "1 is neither prime nor composite."
elif [ $is_prime -eq 1 ]; then
    echo "$number is a prime number."
else
    echo "$number is not a prime number."
fi
3.while loop
Code-
#!/bin/bash
 
echo "Enter a number: "
read number
 
original_number=$number
reverse_number=0
 
while [ $number -gt 0 ]
do
    remainder=$((number % 10))
    reverse_number=$((reverse_number * 10 + remainder))
    number=$((number / 10))
done
 
if [ $original_number -eq $reverse_number ]; then
    echo "$original_number is a palindrome."
else
    echo "$original_number is not a palindrome."
fi
4.until
Code-
#!/bin/bash
echo "Enter a number: "
read number
sum=0
temp=$number
until [ $temp -eq 0 ]
do
    digit=$((temp % 10))
    sum=$((sum + digit ** 3))
    temp=$((temp / 10))
done
if [ $sum -eq $number ]; then
    echo "$number is an Armstrong number."
else
    echo "$number is not an Armstrong number."
fi
5.case
 #!/bin/bash
echo "Enter first number: "
read num1
echo "Enter second number: "
read num2
 
echo "Enter operation (+, -, *, /): "
read operation
 
case $operation in
    +)
        result=$((num1 + num2))
        echo "Result: $result"
        ;;
    -)
        result=$((num1 - num2))
        echo "Result: $result"
        ;;
    \*)
        result=$((num1 * num2))
        echo "Result: $result"
        ;;
    /)
        result=$((num1 / num2))
        echo "Result: $result"
        ;;
    *)
        echo "Invalid operation. Please enter +, -, *, or /."
        ;;
esac

