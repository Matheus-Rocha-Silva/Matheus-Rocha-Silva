package app;

import java.text.ParseException;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;
import java.util.Scanner;

import entities.Department;
import entities.HourContract;
import entities.Worker;
import entities.enums.WorkerLevel;


public class WorkerApp {
	public static void main(String[] args) throws ParseException {
		
		Scanner sc = new Scanner(System.in);
		Locale.setDefault(Locale.US);
		SimpleDateFormat sdf = new SimpleDateFormat("dd/MM/yyyy");
		
		System.out.println("Enter department's name: ");
		String departmentsName = sc.nextLine();
		System.out.println("Enter worker's data: ");
		System.out.println("Name: ");
		String workerName = sc.nextLine();
		System.out.println("Level: ");
		String workerLevel = sc.nextLine();
		System.out.println("Base Salary: ");
		double baseSalary = sc.nextDouble();
		Worker worker = new Worker(workerName, WorkerLevel.valueOf(workerLevel), baseSalary, new Department(departmentsName));
		
		System.out.println("How many contracts to this worker?");
		int n = sc.nextInt();
		
		for(int i = 1; i <= n; i++) {
			System.out.println("Enter contract #"+ i +" data:");
			System.out.println("Date (DD/MM/YYYY): ");
			Date contractDate = sdf.parse(sc.next());
			System.out.println("Value per Hour: ");
			double valuePerHour = sc.nextDouble();
			System.out.print("Duration (hours): ");
			int hours = sc.nextInt();
			HourContract contract = new HourContract(contractDate, valuePerHour, hours);
			worker.addContracts(contract);
		}
		
		System.out.println();
		System.out.println("Enter month and year to calculate income (MM/YYYY): ");
		String monthAndYear = sc.next();
		int month = Integer.parseInt(monthAndYear.substring(0, 2));
		int year = Integer.parseInt(monthAndYear.substring(3));
		System.out.println("Name: "+worker.getName());
		System.out.println("Department: "+worker.getDepartment().getName());
		System.out.println("Income for "+ monthAndYear + ": " + String.format("%.2f", worker.income(year, month)));
		
		sc.close();
	}
}
