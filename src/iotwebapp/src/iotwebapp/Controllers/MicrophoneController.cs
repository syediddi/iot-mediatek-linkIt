using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNet.Mvc;
using Newtonsoft.Json;
using Microsoft.WindowsAzure.Storage;
using Microsoft.WindowsAzure.Storage.Auth;
using Microsoft.WindowsAzure.Storage.Table;

// For more information on enabling MVC for empty projects, visit http://go.microsoft.com/fwlink/?LinkID=397860

namespace iotwebapp.Controllers
{
    [Route("api/iot/myhome/livingroom/[Controller]")]
    public class MicrophoneController : IoTController
    {
        // GET: /<controller>/
        public IActionResult Index()
        {
            return View();
        }

        [HttpPost]
        public IActionResult Post([FromBody]IotMicrophone iotMicrophone)
        {

            // Create the table client.
            CloudTableClient tableClient = storageAccount.CreateCloudTableClient();

            // Create the CloudTable object that represents the "people" table.
            CloudTable table = tableClient.GetTableReference("iot");

            iotMicrophone.PartitionKey = "mic";
            iotMicrophone.RowKey = Guid.NewGuid().ToString();
            // Create the TableOperation object that inserts the customer entity.
            TableOperation insertOperation = TableOperation.Insert(iotMicrophone);
            // Execute the insert operation.
            table.Execute(insertOperation);

            return Ok("Microphone data logged to azure cloud..");

        }
    }

    public class IotMicrophone : TableEntity
    {
        public string deviceid { get; set; }
        public string timeutc { get; set; }
        public string signedby { get; set; }

        
        public string state {
            get
            {
                return JsonConvert.SerializeObject(this.desired);
            }

            set {; }
        }
        public Desired desired { get; set; }
        public class Desired
        {
            public string Intensity { get; set; }
        }

    }

    
    //public class Rootobject
    //{
    //    public Desired desired { get; set; }
    //    public string deviceid { get; set; }
    //    public string timeutc { get; set; }
    //    public string signedby { get; set; }
    //}

    //public class Desired
    //{
    //    public string temperature { get; set; }
    //    public string humidity { get; set; }
    //}

}
