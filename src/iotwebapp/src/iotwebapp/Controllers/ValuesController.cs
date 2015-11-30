using Microsoft.AspNet.Mvc;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace iotwebapp.Controllers
{
    [Route("api/[Controller]")]
    public class ValuesController : Controller
    {
        // GET: api/values
        [HttpGet]
        public IoTState Values()
        {
            return new IoTState { Temperature = "24 C", NodeId = "/iot/home/livingroom/thermostat" };
        }

        [HttpPost]
        public IoTState Post([FromBody]IoTState state)
        {
            return state;
        }
    }

    public class IoTState
    {
        public string Temperature { get; set; }
        public string NodeId { get; set; }

        public override string ToString()
        {
            return JsonConvert.SerializeObject(this);
        }
    }
}
