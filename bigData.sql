-- phpMyAdmin SQL Dump
-- version 4.6.4
-- https://www.phpmyadmin.net/
--
-- Хост: 127.0.0.1
-- Время создания: Авг 30 2017 г., 13:05
-- Версия сервера: 5.7.15
-- Версия PHP: 7.0.10

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- База данных: `bigdata`
--

CREATE DATABASE IF NOT EXISTS `bigdata`;
USE `bigdata`;

-- --------------------------------------------------------

CREATE TABLE `products` (
  `id` int(10) UNSIGNED NOT NULL,
  `article` varchar(30) NOT NULL,
  `description` varchar(255) DEFAULT NULL,
  `count` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;

CREATE TABLE `orders` (
  `id` int(10) UNSIGNED NOT NULL,
  `date` date NOT NULL,
  `count` int(11) NOT NULL,
  INDEX FK_products_orders_id (id),
  CONSTRAINT FK_products_orders_id FOREIGN KEY (id) REFERENCES products (id)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;

-- --------------------------------------------------------

--
-- Индексы таблицы `orders`
--
ALTER TABLE `orders`
  ADD KEY `id` (`id`);
  
ALTER TABLE `products`
  MODIFY `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
