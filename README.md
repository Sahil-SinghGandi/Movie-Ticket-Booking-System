# Movie-Ticket-Booking-System
Movie Ticket Booking System — A menu-driven C++ console application demonstrating OOP, UML-based system design, SOLID principles, modular architecture, seat booking, payment processing, ticket generation, cancellation, and input validation.
# 🎬 Movie Ticket Booking System

A menu-driven C++ console application for managing movie ticket bookings in a single cinema.

## 📌 Features

- 🎥 List currently playing movies
- 🕐 View movie shows with screen and start time
- 💺 Display AVAILABLE / BOOKED seat layout
- 🎟️ Book one or more seats
- 💰 Seat-based pricing:
  - Silver — ₹150
  - Gold — ₹250
  - Platinum — ₹400
- 💳 Payment through UPI, Card, or Cash
- 🎫 Generate and print booking tickets
- ❌ Cancel confirmed bookings
- 🔄 Release seats after failed payment
- ⚠️ Handle invalid menu choices and seat numbers

## 🏗️ Design & OOP

The project demonstrates:

- Encapsulation
- Abstraction
- Inheritance
- Runtime Polymorphism
- Compile-Time Polymorphism
- Static Members
- `this` Keyword
- Composition
- Aggregation
- Association

## 🧩 SOLID Principles

The design applies:

- Single Responsibility Principle
- Open/Closed Principle
- Liskov Substitution Principle
- Dependency Inversion Principle

## 📂 Architecture

The project follows a modular structure with one class per `.cpp` file and no header files, as required by the assignment.

### Main Components

`Movie` · `Seat` · `Screen` · `Cinema` · `Show` · `ShowSeat` · `Customer` · `Booking` · `Payment` · `UpiPayment` · `CardPayment` · `CashPayment` · `PriceCalculator` · `TicketPrinter` · `BookingService`

## 🧪 Edge Cases Tested

- Already-booked seat
- Failed payment
- Booking cancellation
- Invalid seat number
- Invalid menu choice

## 🎯 Project Objective

This project demonstrates how system requirements can be transformed into a structured object-oriented design using UML class diagrams, sequence diagrams, modular C++ implementation, and SOLID principles.
