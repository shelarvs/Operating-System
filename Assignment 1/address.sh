#!/bin/bash

choice=0

create()
{
	if [ -e addressbook.txt ]; then
	
		echo -e "\nAddress book already created"
		
	else
	
		touch addressbook.txt
		echo -e "\nSuccessfully created addressbook"
		
	fi
}

display()
{
	echo -e "\nThe address book is as follows:\n"
	cat addressbook.txt
}

insert()
{
	echo -e "\nEnter record as first name,last name,city,phone number:\n"
	read input
	echo "$input" >> addressbook.txt
	echo -e "\nRecord inserted successfully"
}

delete()
{
	echo -e "\n"
	read -p "Enter the first name of the record you want to delete:" fname
	grep -n "$fname" addressbook.txt
	RETURNSTATUS=`echo $?`
	
	if [ $RETURNSTATUS -eq 1 ]; then
	
		echo -e "\nNo record found for '$fname'"
		
	else
	
		echo -e "\n"
		read -p "Enter the line number of the record you want to delete:" lineNumber
		
		for line in `grep -n "$fname" addressbook.txt`
		do
		
			number=`echo "$line" | cut -c1`
			
			if [ $number -eq $lineNumber ]; then
			
				lineRemove="${lineNumber}d"
				
				sed -i -e "$lineRemove" addressbook.txt
				
				echo -e "\nSuccessfully deleted the record"
				
			else
			
				echo -e "\nWrong line number entered"
			
			fi
		
		done 
 	
	fi 
}

modify()
{
	echo -e "\n"
	read -p "Enter the name of the record you want to modify:" fname	
	grep -n "$fname" addressbook.txt
	RETURNSTATUS=`echo $?`
	
	if [ $RETURNSTATUS -eq 1 ]; then
	
		echo -e "\nNo record found for '$fname'"
		
	else
	
		echo -e "\n"
		read -p "Enter the line number of the record you want to modify:" lineNumber
		
		for line in `grep -n "$fname" addressbook.txt`
		do
		
			number=`echo "$line" | cut -c1`
			
			if [ $number -eq $lineNumber ]; then
			
				lineChange="${lineNumber}s"
				
				echo -e "\nEnter the new data as first name,last name,city,phone number:\n"
				read edit
				
				sed -i -e "$lineChange/.*/$edit/" addressbook.txt
				
				echo -e "\nRecord has been modified successfully"
			
			else
			
				echo -e "\nWrong line number entered"
			
			fi
		
		done 
	
	fi
}

search()
{
	echo -e "\n"
	read -p "Enter the first name of the record you want to search:" fname
	
	grep -n "$fname" addressbook.txt
	RETURNSTATUS=`echo $?`
	
	if [ $RETURNSTATUS -eq 1 ]; then
	
		echo -e "\nNo record found for '$fname'"
		
	else
	
		echo -e "\nRecord found successfully"
	
	fi
}	

while [ $choice -ne 7 ]
do

	echo "================================"
	echo "          ADDRESS BOOK          "
	echo "================================"
	echo "1)Create address book"
	echo "2)View address book"
	echo "3)Insert a record"
	echo "4)Delete a record"
	echo "5)Modify a record"
	echo "6)Search a record"
	echo "7)Exit"
	read -p "Enter your choice:" choice

	if [ $choice -lt 1 ] || [ $choice -gt 7 ]; then
	
		echo -e "\nInvalid choice!"
		
	else

		case $choice in

			1) create ;;
	
			2) display ;;
	
			3) insert ;;
	
			4) delete ;;
	
			5) modify ;;
			
			6) search ;;
	
			7) exit 0 ;;
		
		esac
		
	fi

done
