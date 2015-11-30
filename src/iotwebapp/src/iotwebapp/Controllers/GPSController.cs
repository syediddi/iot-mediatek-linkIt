using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNet.Mvc;
using Microsoft.WindowsAzure.Storage.Table;
using Newtonsoft.Json;

// For more information on enabling Web API for empty projects, visit http://go.microsoft.com/fwlink/?LinkID=397860

namespace iotwebapp.Controllers
{
    [Route("api/iot/mydevice/location/[Controller]")]
    public class GPSController : IoTController
    {
        [HttpPost]
        public IActionResult Post([FromBody]IotGPS iotGPS)
        {
            // Create the table client.
            CloudTableClient tableClient = storageAccount.CreateCloudTableClient();

            // Create the CloudTable object that represents the "people" table.
            CloudTable table = tableClient.GetTableReference("iot");

            iotGPS.PartitionKey = "gps";
            iotGPS.RowKey = Guid.NewGuid().ToString();
            // Create the TableOperation object that inserts the customer entity.
            TableOperation insertOperation = TableOperation.Insert(iotGPS);
            // Execute the insert operation.
            table.Execute(insertOperation);

            return Ok("GPS data logged to azure cloud..");
        }
    }


    public class IotGPS : TableEntity
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
            public string lat { get; set; }
            [JsonProperty("long")]
            public string longitude { get; set; }

        }

    }
}
