﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNet.Mvc;
using Microsoft.WindowsAzure.Storage.Table;
using Newtonsoft.Json;

// For more information on enabling Web API for empty projects, visit http://go.microsoft.com/fwlink/?LinkID=397860

namespace iotwebapp.Controllers
{
    [Route("api/iot/myhome/room/[controller]")]
    public class LivingRoomController : IoTController
    {
        [HttpPost]
        public IActionResult Post([FromBody]IotLivingRoom iotLivingRoom)
        {
            // Create the table client.
            CloudTableClient tableClient = storageAccount.CreateCloudTableClient();

            // Create the CloudTable object that represents the "people" table.
            CloudTable table = tableClient.GetTableReference("iot");

            iotLivingRoom.PartitionKey = "livingroom";
            iotLivingRoom.RowKey = Guid.NewGuid().ToString();
            // Create the TableOperation object that inserts the customer entity.
            TableOperation insertOperation = TableOperation.Insert(iotLivingRoom);
            // Execute the insert operation.
            table.Execute(insertOperation);

            return Ok("Living room attributes logged to azure cloud..");
        }
    }

    public class IotLivingRoom : TableEntity
    {
        public string deviceid { get; set; }
        public string timeutc { get; set; }
        public string signedby { get; set; }


        public string state
        {
            get
            {
                return JsonConvert.SerializeObject(this.desired);
            }

            set {; }
        }
        public Desired desired { get; set; }
        public class Desired
        {
            public string window { get; set; }
            public string door { get; set; }
            public string ac { get; set; }
            public string temperature { get; set; }
            public string humidity { get; set; }


        }

    }
}
