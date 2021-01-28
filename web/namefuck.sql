-- phpMyAdmin SQL Dump
-- version 4.7.7
-- https://www.phpmyadmin.net/
--
-- Хост: localhost
-- Время создания: Июн 23 2018 г., 23:42
-- Версия сервера: 5.7.21-20-beget-5.7.21-20-1-log
-- Версия PHP: 5.6.30

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- База данных: `karlend_cheat`
--

-- --------------------------------------------------------

--
-- Структура таблицы `auth`
--
-- Создание: Май 05 2018 г., 14:37
-- Последнее обновление: Май 19 2018 г., 17:11
--

DROP TABLE IF EXISTS `auth`;
CREATE TABLE `auth` (
  `id` int(11) NOT NULL,
  `hwid` text NOT NULL,
  `csgo_time` text,
  `idk_time` text,
  `banned` text NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Дамп данных таблицы `auth`
--

INSERT INTO `auth` (`id`, `hwid`, `csgo_time`, `idk_time`, `banned`) VALUES
(1, '2187f0ace8e7bc41370fa478b793e8ce', '10-05-2028', '0', 'no'),
(2, 'a625fdab1bc2e9546f16c12b1a0dd4ee', '15-05-2018', '0', 'no'),
(3, '52b3920fe91b221ceef2546d4e0ce6dc', '31-03-4756', '0', 'no'),
(4, 'b11531d0e2a5b9b0fc4497e031331255', '24-06-2018', '0', 'no'),
(5, 'd802f2f0405a827c3adbdba17cc1f97b', '06-06-2018', '0', 'no'),
(7, '0adcb112c69b5779b2a0739be4f53b84', '30-09-2045', '0', 'no'),
(8, '08a307c26620b6f2650cd4e86289d1eb', '21-06-2018', '0', 'no');

-- --------------------------------------------------------

--
-- Структура таблицы `licensekeys`
--
-- Создание: Май 05 2018 г., 14:37
--

DROP TABLE IF EXISTS `licensekeys`;
CREATE TABLE `licensekeys` (
  `activationkey` text NOT NULL,
  `cheat` text NOT NULL,
  `day` text NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Дамп данных таблицы `licensekeys`
--

INSERT INTO `licensekeys` (`activationkey`, `cheat`, `day`) VALUES
('KGIDB-J6GZP-F14CW-R1MWQ', '1', '5'),
('QP6RV-T6C8N-FIUOM-VYI2O', '1', '5'),
('B6SCW-GSK1Y-FERV0-096N5', '1', '1');

--
-- Индексы сохранённых таблиц
--

--
-- Индексы таблицы `auth`
--
ALTER TABLE `auth`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT для сохранённых таблиц
--

--
-- AUTO_INCREMENT для таблицы `auth`
--
ALTER TABLE `auth`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=9;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
