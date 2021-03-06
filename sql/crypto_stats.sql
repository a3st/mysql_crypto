-- MySQL dump 10.13  Distrib 8.0.24, for Win64 (x86_64)
--
-- Host: 192.168.1.95    Database: crypto
-- ------------------------------------------------------
-- Server version	8.0.24

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `stats`
--

DROP TABLE IF EXISTS `stats`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `stats` (
  `id` int NOT NULL,
  `difficult` bigint DEFAULT NULL,
  `next_difficult` bigint DEFAULT NULL,
  `blockchain_size` float DEFAULT NULL,
  `blocks` int DEFAULT NULL,
  `transactions` bigint DEFAULT NULL,
  `outputs` bigint DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3 COMMENT='Статистика монет';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `stats`
--

LOCK TABLES `stats` WRITE;
/*!40000 ALTER TABLE `stats` DISABLE KEYS */;
INSERT INTO `stats` VALUES (0,20608845737768,28606587777079,344866000000,683338,641731589,1733912177),(1,13892355522,0,151991000000,686162,297038654,791161847),(2,498026696292,0,162759000000,687652,329715746,864108502),(3,130431034406,0,342382000000,686954,614652171,1407304490),(4,0,0,7398880000,5709744,7364701,0),(5,159126731,0,21607000000,1469862,36142582,118459488),(6,4254534,0,43747800000,3726567,75245270,223397648),(7,0,0,0,183396403,0,0),(8,7593145988552737,0,233312000000,12421945,1129245183,0),(9,1238866,0,1979150000,3585205,4695491,8844115),(10,12368328,12137281,40094700000,2051258,70275639,224565704),(11,0,0,0,0,0,0),(12,300104779301,0,0,2359529,13529723,0),(13,0,0,0,0,0,0),(14,0,0,0,0,0,0),(15,0,0,0,1466368,0,0),(16,59228449,0,26665400000,1247312,8495096,136634122);
/*!40000 ALTER TABLE `stats` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2021-05-13  5:38:20
