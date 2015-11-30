using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNet.Mvc;
using Microsoft.WindowsAzure.Storage;
using Microsoft.WindowsAzure.Storage.Auth;

// For more information on enabling MVC for empty projects, visit http://go.microsoft.com/fwlink/?LinkID=397860

namespace iotwebapp.Controllers
{
    public class IoTController : Controller
    {
        public CloudStorageAccount storageAccount = new CloudStorageAccount(new StorageCredentials("your-account-name", "your-key"), true);
    }
}
