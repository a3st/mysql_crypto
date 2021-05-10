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
-- Table structure for table `currency`
--

DROP TABLE IF EXISTS `currency`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `currency` (
  `id` int NOT NULL,
  `coin_name` char(45) DEFAULT NULL,
  `value` float DEFAULT NULL,
  `market_cap` bigint DEFAULT NULL,
  `dominance` float DEFAULT NULL,
  KEY `fk_id_idx` (`id`),
  CONSTRAINT `currency_to_mem_pool_fk` FOREIGN KEY (`id`) REFERENCES `mem_pool` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `currency_to_stats_fk` FOREIGN KEY (`id`) REFERENCES `stats` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3 COMMENT='Стоимость монет';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `currency`
--

LOCK TABLES `currency` WRITE;
/*!40000 ALTER TABLE `currency` DISABLE KEYS */;
INSERT INTO `currency` VALUES (0,'bitcoin',57518,1073254049010,42.26),(1,'bitcoin-abc',36.15,676876067,0.03),(2,'bitcoin-cash',1434.27,27101715356,1.07),(3,'bitcoin-sv',345.24,6544596282,0.26),(4,'cardano',1.71,55312072555,2.18),(5,'dash',399.85,4054019983,0.16),(6,'dogecoin',0.48495,62822962435,2.47),(7,'eos',9.96,9619970082,0.38),(8,'ethereum',4111.82,476218921517,18.75),(9,'groestlcoin',1.59,122888586,0),(10,'litecoin',380.08,25371303481,1),(11,'mixin',0,0,0),(12,'monero',464.64,8319999452,0.33),(13,'ripple',1.52,70022609869,2.76),(14,'stellar',0.705986,16281171635,0.64),(15,'tezos',6.69,5172566855,0.2),(16,'zcash',309.33,3427213745,0.13);
/*!40000 ALTER TABLE `currency` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2021-05-10 23:04:18
